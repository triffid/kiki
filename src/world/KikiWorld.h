/*
 *  KikiWorld.h
 */

#ifndef __KikiWorld
#define __KikiWorld

#include "KikiPos.h"
#include "KikiCell.h"
#include "KikiLight.h"
#include "KikiController.h"

#include <KPickHandler.h>

class KikiAction;
class KikiBot;
class KLightingProjection;

// __________________________________________________________________________________________________
class KikiWorld : public KPickHandler
{
    public: // ........................................................................ PUBLIC

    // ........................................................................ enums
    enum {  	DISPLAY_BORDER = KDL_PICKHANDLER_FLAG_END,
                DISPLAY_RASTER, 
                DISPLAY_DOTS,
                DISPLAY_SHADOWS,
                WORLD_END };
                
    enum {  	CAMERA_INSIDE, CAMERA_BEHIND, CAMERA_FOLLOW };
    
    enum {	TEXTURE_GRADIENT };
        
    // ........................................................................ init & display
    void 	init 			();
    void	reinit			();
    void	initializeTextures	();
    void	displayWall 		( int width, int height );
    void	display 		( int mode );
    void 	displayPickables	( int mode );
    void	deleteDisplayList	();	
    
    // ........................................................................ camera & projection
    void	changeCameraMode	();
    int		getCameraMode		() const { return camera_mode; }
    void	setCameraMode		( int mode );
    
    void	setEditMode		( bool editMode );
    bool	getEditMode		() { return edit_mode; }
    
    KProjection * getProjection 	();
    
    GLuint	getTextureId 		( int tenum ) { return texture_ids[tenum]; }
    
    // ........................................................................ world size
    void	setSize 		(int x, int y, int z = 0);
    KikiSize	getSize			() const { return size; }
    float	getMaxDistance		() const { return max_distance; }
    
    void	setName			( const std::string & n ) { name = n; }
    std::string getName			() const { return name; }
    
    // ........................................................................ pickhandler 
    void	picked			();
    bool	shouldPick		( const KPickable * );
    void	moved			( const KMouseEvent & mouseEvent );
    const KPickable * getPickableWithId ( int ) const;

    void	focusOnPickedPickable	( bool zoom = false );

    // ........................................................................ object handling

    void	addObject		( KikiObject * object );
    void  	deleteObject	 	( KikiObject * object );

    void      	addObjectAtPos   	( KikiObject * object, const KikiPos & pos );
    void      	setObjectAtPos   	( KikiObject * object, const KikiPos & pos );
    void  	unsetObject	 	( KikiObject * object );
    void  	removeObject	 	( KikiObject * object );
    void  	deleteAllObjects	();
    void	deleteObjectsWithClassName ( const std::string & className );
    KikiObject* getObjectWithName	( const std::string & objectName );

    bool	moveObjectToPos 	( KikiObject * object, const KikiPos & pos );
    bool 	mayObjectPushToPos	( KikiObject * object, const KikiPos & pos, int duration );
    void	objectWillMoveToPos 	( KikiObject * object, const KikiPos & pos, int duration );	
    void	objectMovedFromPos	( KikiObject * object, const KikiPos & pos );

    // ........................................................................ pos accessors
    KikiBot * 		getBotAtPos 		( const KikiPos & pos ) const;
    KikiObject * 	getOccupantAtPos 	( const KikiPos & pos ) const;
    KikiObject * 	getRealOccupantAtPos 	( const KikiPos & pos ) const;
    KikiObject *	getObjectOfTypeAtPos 	( const KClassId & classId, const KikiPos & pos ) const;
    KikiObjectList	getObjectsOfTypeAtPos 	( const KClassId & classId, const KikiPos & pos ) const;
    KikiObjectList	getObjectsOfType 	( const KClassId & classId ) const;
    
    void		setDisplayRaster	( bool b ) { flags[DISPLAY_RASTER] = b; deleteDisplayList();}
    void		setDisplayBorder  	( bool b ) { flags[DISPLAY_BORDER] = b; deleteDisplayList();}
    void		setDisplayShadows  	( bool b ) { flags[DISPLAY_SHADOWS] = b; }
    
    void		setRasterSize		( float s ) { raster_size = s; deleteDisplayList(); }
    
    // ........................................................................ position helpers
    KikiPos	getNearestValidPos	( const KikiPos & pos ) const;
    float	getWallDistanceForRay	( const KVector & rayPos, const KVector & rayDirection );
    KVector	getInsideWallPosWithDelta ( const KVector & pos, float delta );
    float	getWallDistanceForPos	( const KVector & pos );
    bool	isInvalidPos		( const KikiPos & pos ) const { return !isValidPos(pos); }
    bool	isValidPos		( const KikiPos & pos ) const
                                        { 
                                            return (pos.x >= 0 && pos.x < size.x &&
                                                    pos.y >= 0 && pos.y < size.y &&
                                                    pos.z >= 0 && pos.z < size.z);
                                        }
    bool	isUnoccupiedPos		( const KikiPos & pos ) const;
    bool	isOccupiedPos		( const KikiPos & pos ) const;
    int		posToIndex 		( const KikiPos & pos ) const
                                        { 
                                            return (pos.x * size.z * size.y + pos.y * size.z + pos.z); 
                                        }
    KikiPos	indexToPos 		( int index ) const
                                        { 
                                            int lsize = size.z * size.y;
                                            int lrest = index % lsize;
                                            return KikiPos (index / lsize, lrest / size.z, lrest % size.z); 
                                        }

    // ........................................................................ debugging
    void		debugLine	( const KVector & p1, const KVector & p2, const KColor & c = KColor());

    protected: // ..................................................................... PROTECTED

    INTROSPECTION
    KIKI_COLOR_HEADER

    friend class	KikiController;
    
    unsigned int	display_list;
    
    KikiObjectList	objects;
    KikiLightList	lights;
    
    KikiCellList	cells;		// the world
    KikiSize 		size; 		// it's size
    
    std::vector<GLuint> texture_ids;
    
    std::string		name;
    
    float		max_distance;	// maximum distance in this world (for sound)
    
    float		raster_size;	// distance between wall plates
    
    KPosition 		deltas;		// drag deltas since activating 
    KVector 		drag_start_pos;	// dragged items start position 
    
    KikiObjectList	moved_objects;	// objects that moved (resolved in update status)
    
    KLightingProjection * edit_projection;
    KLightingProjection * player_projection;
    
    bool		edit_mode;
    
    bool		debug_camera;
    bool		debug_cells;
    
    int 		camera_mode;	// inside, behind, follow or preview

    // ........................................................................ (con/de)struction
                        KikiWorld	();
                        ~KikiWorld	();

    // ........................................................................ display, lights & shadows
    
    std::vector< std::pair<KVector, KColor> > debug_edges;
    std::vector< std::vector<KVector> > shadow_faces;

    void		displayDebug	();
    void		displayLights	();
    void		displayShadows	();
        
    void		shadowsForLight	( KikiLight * light );
    void		calculateShadows();
    
    void		updateStatus	(); // replaces temporary objects with moved objects
    KikiCell * 		getCellAtPos	( const KikiPos & pos ) const;
};

#endif

