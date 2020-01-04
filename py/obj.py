
from math import *
import os
import types

# .................................................................................................................
#                                                       ObjFileConverter
#
#                                           creates header files from .obj models
# .................................................................................................................

class ObjFileConverter:
    """loads a .obj file and writes a .h header file with arrays for triangles, quads, triangle fans and quad strips"""
    
    # ................................................................................................................
    def __init__(self, file_path, object_name = ""):
        """initialization with path to .obj file and optional object name"""
                
        try:
            file = open (file_path, "r")
            self.file_path = file_path
        except:
            try: 
                file = open (file_path + ".obj", "r")
                self.file_path = file_path + ".obj"
            except:
                print("[*** Error ***] unable to open file", file_path)
                return
    
        if object_name:
            self.object_name = object_name
        else:
            self.object_name = self.file_path[:self.file_path.find(".")]
        
        self.dir_path = os.path.dirname (self.file_path)
        if self.dir_path: self.dir_path += "/"

        self.lines = file.readlines()
        self.line  = 0
        
        self.vertices   = []
        self.normals    = []
        self.quads      = []
        self.triangles  = []
        self.strips     = []
        self.fans       = []
        
        self.parseObjects()
        self.optimizeFaces()

        print("\nsummary:")
        print("vertices/normals:", len (self.vertices), len (self.normals))
        print("triangles:       ", len (self.triangles))
        print("quads:           ", len (self.quads))
        print("fans:            ", len (self.fans))
        print("strips:          ", len (self.strips))

        self.generateArrays()

    # ................................................................................................................     
    def parseObjects (self):
        """collects objects"""
            
        if self.line >= len(self.lines): return

        while self.lines[self.line][0:2] != "o ":
            self.line += 1
            if self.line >= len(self.lines): return            
            
        print("\nobject", self.lines[self.line][2:])

        num_v = len (self.vertices)
        num_n = len (self.normals)
        num_t = len (self.triangles)
        num_q = len (self.quads)

        self.parseVertices()
        self.parseNormals()
        self.parseFaces()
        
        print("vertices/normals:", len (self.vertices) - num_v, len (self.normals) - num_n)
        print("triangles:       ", len (self.triangles) - num_t)
        print("quads:           ", len (self.quads) - num_q)
        print("")
        
        self.parseObjects()
  
    # ................................................................................................................     
    def parseVertices (self):
        """collects vertices"""
            
        while self.lines[self.line][0:2] != "v ":
            self.line += 1
            
        while self.lines[self.line][0:2] == "v ":
            self.vertices.append (map(float, self.lines[self.line][2:].split()))

            self.line += 1

    # ................................................................................................................     
    def parseNormals (self):
        """collects normals"""
        
        while self.lines[self.line][0:2] == "vn":
            normal_coords = map (float, self.lines[self.line][2:].split())
            link = false
            for normal in self.normals:
                if normal == normal_coords: 
                    link = self.normals.index(normal)
                    break
            if link:
                self.normals.append (link)
            else:
                self.normals.append (normal_coords)
            self.line += 1
    
    # ................................................................................................................        
    def parseFaces (self):
        """collects faces into triangle and quad lists"""
        
        while self.lines[self.line][0:2] != "f ":
            self.line += 1
            
        while self.lines[self.line][0:2] == "f ":
            
            zipped_list = map (lambda s: (int(s.split("//")[0])-1, int(s.split("//")[1])-1), \
                                                            self.lines[self.line][2:].split())

            vertex_list = map (lambda s: s[0], zipped_list)
            normal_list = map (lambda s: s[1], zipped_list)

            for normal_index in normal_list:
                if type (self.normals[normal_index]) == types.IntType:
                    vertex_list.append (self.normals[normal_index])
                else:
                    vertex_list.append (normal_index)

            if len (vertex_list) == 6:
                self.triangles.append (vertex_list)
            else:
                self.quads.append (vertex_list)
                
            self.line += 1
            if self.line >= len (self.lines): 
                return

    # ................................................................................................................
    def optimizeFaces (self):
        """creates triangle fans and quad strips from collected triangles and quads"""
        
        def shift_quad (quad, shift=-2):
            return  quad[(4-shift)%4:4]  + quad[:(4-shift)%4] + \
                    quad[4+(4-shift)%4:] + quad[4:4+(4-shift)%4]

        def shift_triangle (triangle, shift):
            return  triangle[(3-shift)%3:3]  + triangle[:(3-shift)%3] + \
                    triangle[3+(3-shift)%3:] + triangle[3:3+(3-shift)%3]

        def equal_quad (q, p):
            for i in range(1,5):
                s = shift_quad(p, i)
                if q == s: return i
            return 0

        # ................................................................... quad strips

        strips = []                                                         # seed strip search with pairs
                                                                            # of neighboring quads
        for quad in self.quads:                                             # for each quad
            for q in self.quads[self.quads.index(quad)+1:]:                     # loop over remaining quads
                for i in range(4):                                                  # search for same edge
                    for j in range(4):
                        squad = shift_quad (quad, 2-i)
                        sq    = shift_quad (q, -((i+j)%4))
                        if squad[2] == sq[1] and squad[3] == sq[0] and \
                            squad[6] == sq[5] and squad[7] == sq[4]:                 # same edge found
                            strips.append ([squad, sq])                                 # create new strip
            
        if len (strips):  
            remove = 1
            while remove:
                for strip in strips:                                                # for each strip
                    remove = []
                    s1 = strip
                    for s2 in strips[strips.index(s1)+1:]:                              # loop over other strips
                        if s1[-1][:4] == s2[0][:4]:                                         # join, if matching
                            s1 = s1 + s2[1:]                                                # head or tail
                            remove.append (s2)
                        elif s2[-1][:4] == s1[0][:4]:
                            s1 = s2 + s1[1:]
                            remove.append (s2)
                        elif s1[0][:4] == shift_quad (s2[0])[:4]:                           # eventually reverse
                            reversed = map (shift_quad, s2)                                 # other strip
                            reversed.reverse() 
                            s1 = reversed + s1[1:]
                            remove.append (s2)
                        elif s1[-1][:4] == shift_quad (s2[-1])[:4]:
                            reversed = map (shift_quad, s2)
                            reversed.reverse()
                            s1 = s1 + reversed[1:]
                            remove.append (s2)
    
                    if remove:                                                      # if strips have been joined
                        strips.remove (strip)                                           # remove joined strips
                        for s in remove:
                            if s in strips:
                                strips.remove (s)
                        strips.insert (0, s1)                                           # insert join
    
            
            strips.sort (lambda a, b: len (b) - len (a))                        # sort strips by length
            
            for strip in strips:                                                # filter strips ...
                use_strip = 1
                for quad in strip:                                                  # loop over quads in strip
                    found = 0                                                           # and search them in quadlist
                    for q in self.quads:
                        if equal_quad (quad, q):                                        # quad found
                            found = 1                                                       # continue with next quad
                            break
                    if not found:                                                       # quad not found
                        use_strip = 0                                                       # don't use strip
                        break
    
                if use_strip:                                                       # no used quad found
                    self.strips.append (strip)                                          # store strip
                    for quad in strip:                                                  # remove its quads from quadlist
                        index = 0
                        while index < len (self.quads):
                            if equal_quad (quad, self.quads[index]):
                                del self.quads[index]
                            else:
                                index += 1
    
        # ................................................................... triangle fans
        fans = {}
        
        for triangle in self.triangles:
            for t in self.triangles:
                for i in range (3):
                    for j in range (3):
                        if triangle[i] == t[(i+j)%3] and triangle[(i+2)%3] == t[(i+j+1)%3] and \
                            triangle[i+3] == t[(i+j)%3+3] and triangle[(i+2)%3+3] == t[(i+j+1)%3+3]:
                            if triangle[i] in fans:
                                fan = fans[triangle[i]]
                                if fan[-1] == triangle:
                                    fan.append (t)
                                elif fan[0] == t:
                                    fan.insert (0, triangle)
                            else:
                                fans[triangle[i]] = [triangle, t]

        for fan in fans: 
            if fans[fan][0] == fans[fan][-1]:
                fans[fan].pop()

        fans = fans.values()
        fans.sort (lambda a, b: len (b) - len (a))

        for fan in fans:
            use_fan = 0
            for triangle in fan:
                if triangle in self.triangles:
                    use_fan = 1
                    self.triangles.remove (triangle)
            if use_fan: self.fans.append (fan)

        for fan in self.fans:
            for index in range (len(fan)-1):
                t1 = fan[index]
                t2 = fan[index+1]
                for i in range(3):
                    for j in range(3):
                        if t1[i] == t2[(i+j)%3] and t1[(i+2)%3] == t2[(i+j+1)%3]:
                            fan[index]   = shift_triangle (t1,-i)
                            fan[index+1] = shift_triangle (t2,-(i+j)%3)

    # ................................................................................................................
    def generateArrays (self):
        """writes the header file with arrays for the collected triangles, quads, fans and strips"""
        
        result = []

        result.append ("#ifndef __obj_%s" % (self.object_name,))
        result.append ("#define __obj_%s" % (self.object_name,))

        # ................................................................... render macro

        result.append ("\n#define render_%s { \\" % (self.object_name,))

        if self.triangles:
            result.append ("    glInterleavedArrays (GL_N3F_V3F, 0, %sInterleavedTriangles); \\" % \
                                                            (self.object_name,))
            result.append ("    glDrawArrays (GL_TRIANGLES, 0, %sNumTriangles*3); \\" % \
                                                            (self.object_name,))

        if self.quads:
            result.append ("    glInterleavedArrays (GL_N3F_V3F, 0, %sInterleavedQuads); \\" % \
                                                            (self.object_name,))
            result.append ("    glDrawArrays (GL_QUADS, 0, %sNumQuads*4); \\" % (self.object_name,))

        if self.strips:
            result.append ("    glInterleavedArrays (GL_N3F_V3F, 0, %sInterleavedQuadStrips); \\" % \
                                                            (self.object_name,))
            result.append ("    for (int i = 0; i < %sNumQuadStrips; i++) { \\" % (self.object_name,))
            result.append ("        glDrawArrays (GL_QUAD_STRIP, %sQuadStripIndices[i]/6, \\"  % (self.object_name,))
            result.append ("                        (%sQuadStripIndices[i+1] - %sQuadStripIndices[i])/6); \\" % \
                                                            (self.object_name, self.object_name))
            result.append ("    } \\")

        if self.fans:
            result.append ("    glInterleavedArrays (GL_N3F_V3F, 0, %sInterleavedTriangleFans); \\" % \
                                                            (self.object_name,))
            result.append ("    for (int i = 0; i < %sNumTriangleFans; i++) { \\" % (self.object_name,))
            result.append ("        glDrawArrays (GL_TRIANGLE_FAN, %sTriangleFanIndices[i]/6, \\" % \
                                                            (self.object_name,))
            result.append ("                        (%sTriangleFanIndices[i+1] - %sTriangleFanIndices[i])/6); \\" % \
                                                            (self.object_name, self.object_name))
            result.append ("    } \\")

        result.append ("}\n")

        # ................................................................... triangles
        
        if self.triangles:
            result.append ("static int %sNumTriangles = %d;" % \
                                (self.object_name, len (self.triangles)))
            result.append ("static float %sInterleavedTriangles[%d] = {" % \
                                (self.object_name, len (self.triangles)*18))
        
            for triangle in self.triangles:
                line = ""
                for i in range (3):
                    line += "%6.3f, %6.3f, %6.3f,"   % tuple (self.normals[triangle[i+3]])
                    line += "%6.3f, %6.3f, %6.3f,\n" % tuple (self.vertices[triangle[i]])
                result.append (line)
                
            result.append("};\n")

        # ................................................................... quads

        if self.quads:
            result.append("static int %sNumQuads = %d;" % (self.object_name, len (self.quads)))
            result.append("static float %sInterleavedQuads[%d] = {" % \
                                (self.object_name, len (self.quads)*24))
            
            for quad in self.quads:
                line = ""
                for i in range (4):
                    line += "%6.3f, %6.3f, %6.3f,"   % tuple (self.normals[quad[i+4]])
                    line += "%6.3f, %6.3f, %6.3f,\n" % tuple (self.vertices[quad[i]])
                result.append (line)
                
            result.append("};\n")

        # ................................................................... quad strips

        if self.strips:
            result.append("static int %sNumQuadStrips = %d;\n" % (self.object_name, len (self.strips)))
            
            line  = "static int %sQuadStripIndices[%d] = { " % (self.object_name, len (self.strips)+1)
            index = 0
            for strip in self.strips:
                line += "%d, " % (index,)
                index += len (strip) * 12 + 12
            line += "%d" % (index,)    
            result.append(line + " };\n")

            result.append("static float %sInterleavedQuadStrips[%d] = {" % (self.object_name, index))
            
            for strip in self.strips:
                
                line = ""
                line += "%6.3f, %6.3f, %6.3f, " % tuple (self.normals[strip[0][4]])
                line += "%6.3f, %6.3f, %6.3f, " % tuple (self.vertices[strip[0][0]])
                
                line += "%6.3f, %6.3f, %6.3f, " % tuple (self.normals[strip[0][5]])
                line += "%6.3f, %6.3f, %6.3f,"  % tuple (self.vertices[strip[0][1]])

                result.append(line)                

                for quad in strip:
                    line = ""
                    line += "%6.3f, %6.3f, %6.3f, " % tuple (self.normals[quad[7]])
                    line += "%6.3f, %6.3f, %6.3f, " % tuple (self.vertices[quad[3]])
                    result.append (line)
                    
                    line = ""
                    line += "%6.3f, %6.3f, %6.3f, " % tuple (self.normals[quad[6]])
                    line += "%6.3f, %6.3f, %6.3f, " % tuple (self.vertices[quad[2]])
                    result.append (line)
                
            result.append("};\n")          

        # ................................................................... fans

        if self.fans:
            result.append("static int %sNumTriangleFans = %d;\n" % (self.object_name, len (self.fans)))
            
            line  = "static int %sTriangleFanIndices[%d] = { " % (self.object_name, len (self.fans)+1)
            index = 0
            
            for fan in self.fans:                
                line += "%d, " % (index,)
                index += len (fan) * 6 + 12
            
            line += "%d" % (index,)    
            result.append(line + " };\n")

            result.append("static float %sInterleavedTriangleFans[%d] = {" % (self.object_name, index))
            
            for fan in self.fans:
                
                line = ""
                line += "%6.3f, %6.3f, %6.3f, " % tuple (self.normals[fan[0][0+3]])
                line += "%6.3f, %6.3f, %6.3f, " % tuple (self.vertices[fan[0][0]])
                
                line += "%6.3f, %6.3f, %6.3f, " % tuple (self.normals[fan[0][1+3]])
                line += "%6.3f, %6.3f, %6.3f, " % tuple (self.vertices[fan[0][1]])

                result.append(line)                

                for triangle in fan:
                    line = ""
                    line += "%6.3f, %6.3f, %6.3f, " % tuple (self.normals[triangle[2+3]])
                    line += "%6.3f, %6.3f, %6.3f, " % tuple (self.vertices[triangle[2]])
                    result.append (line)
                                    
            result.append("};\n")          

        result.append ("#endif // __obj_%s" % (self.object_name,))

        # ................................................................... save header file
        
        file_path = self.dir_path + self.object_name + ".h"

        try:
            file = open (file_path, "w")
        except:
            print("[*** Error ***] unable to open file for writing ", file_path)
            return 0
        
        file.write("\n".join(result))
        file.close()
        print("\noutput written to", file_path)

        file_path = "/Users/kodi/Projects/kiki/src/items/" + self.object_name + ".h"

        try:
            file = open (file_path, "w")
        except:
            print("[*** Error ***] unable to open file for writing ", file_path)
            return 0
        
        file.write("\n".join(result))
        file.close()
        print("\noutput written to", file_path)


#ObjFileConverter("/Users/kodi/Projects/kiki/misc/objects/body.obj", "body")
#ObjFileConverter("/Users/kodi/Projects/kiki/misc/objects/test.obj", "test")
#ObjFileConverter("/Users/kodi/Projects/kiki/misc/objects/gear.obj", "gear")
#ObjFileConverter("/Users/kodi/Projects/kiki/misc/objects/valve.obj", "valve")
#ObjFileConverter("/Users/kodi/Projects/kiki/misc/objects/cylinder.obj", "cylinder")

#ObjFileConverter("/Users/kodi/Projects/kiki/misc/objects/wire.obj", "wire")
#ObjFileConverter("/Users/kodi/Projects/kiki/misc/objects/motor.obj", "motor")
#ObjFileConverter("/Users/kodi/Projects/kiki/misc/objects/generator.obj", "generator")

#ObjFileConverter("/Users/kodi/Projects/kiki/misc/objects/kolben.obj", "kolben")

#ObjFileConverter("/Users/kodi/Projects/kiki/misc/objects/tire.obj", "tire")
#ObjFileConverter("/Users/kodi/Projects/kiki/misc/objects/cross_tire.obj", "cross_tire")
#ObjFileConverter("/Users/kodi/Projects/kiki/misc/objects/wirestone.obj", "wirestone")
ObjFileConverter("/Users/kodi/Projects/kiki/misc/objects/mutant.obj", "mutant")


