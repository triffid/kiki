/*
 *  KIntrospection.h
 *  kodisein
 */

#ifndef __KIntrospection
#define __KIntrospection

#ifdef WIN32
#pragma warning ( disable : 4800 4305 4267 ) // Disable warnings
#endif

#include <string>

// --------------------------------------------------------------------------------------------------------
class KClassInfo
{
    const char * 	name;
    const KClassInfo ** bases;
    public:
    KClassInfo (const char * n, const KClassInfo ** b) : name(n), bases(b) {}
    const char * getName() const { return name; }
    void         getHierarchy( std::string & ) const;
    bool         canCastTo( const KClassInfo * ) const; 
    bool         hasBase( const KClassInfo * ) const; 
    bool         hasDirectBase( const KClassInfo * ) const; 
    bool	 sameClass( const KClassInfo * cip ) const { return(this==cip||strcmp(name,cip->name)==0);}
};

// --------------------------------------------------------------------------------------------------------
class KClassId
{
    private:
    const KClassInfo * class_id;
    public:
    KClassId(const KClassInfo * cid) : class_id(cid) {}
    const KClassInfo * getClassInfo () const { return class_id; }
    bool isEmpty() const { return class_id == NULL; }
    int operator==(KClassId i) const { return class_id->sameClass(i.class_id); }
    int operator!=(KClassId i) const { return !class_id->sameClass(i.class_id); }
    int operator>=(KClassId i) const { return class_id->canCastTo(i.class_id); }
    int operator<=(KClassId i) const { return i.class_id->canCastTo(class_id); }
    int operator< (KClassId i) const { return i.class_id->hasBase(class_id); }
    int operator> (KClassId i) const { return class_id->hasBase(i.class_id); }
};

#define INTROSPECTION \
    public: \
    static   const KClassInfo   class_info; \
    virtual  const KClassId     getClassId() const { return &class_info; }; \
    static   const KClassId 	classId() { return &class_info; } \
    const char * getClassName () const { return getClassId().getClassInfo()->getName(); } \
    private:

#define INTROSPECTION_BASE_LIST(className) \
    static const KClassInfo * className ## BaseList[] = { 0 };

#define INTROSPECTION_BASE_LIST1(className,base1) \
    static const KClassInfo * className ## BaseList[] = { &base1::class_info, 0 };
    
#define INTROSPECTION_BASE_LIST2(className,base1,base2) \
    static const KClassInfo * className ## BaseList[] = { &base1::class_info, &base2::class_info, 0 };

#define INTROSPECTION_BASE_LIST3(className,base1,base2,base3) \
    static const KClassInfo * className ## BaseList[] = \
            { &base1::class_info, &base2::class_info, &base3::class_info, 0 };

#define CLASS_INFO_DEFINITION(className) \
    const KClassInfo className::class_info(#className, className ## BaseList);

#define KDL_CLASS_INTROSPECTION(className) \
    INTROSPECTION_BASE_LIST(className) CLASS_INFO_DEFINITION(className)

#define KDL_CLASS_INTROSPECTION_1(className,base1) \
    INTROSPECTION_BASE_LIST1(className,base1) CLASS_INFO_DEFINITION(className)
    
#define KDL_CLASS_INTROSPECTION_2(className,base1,base2) \
    INTROSPECTION_BASE_LIST2(className,base1,base2) CLASS_INFO_DEFINITION(className)

#define KDL_CLASS_INTROSPECTION_3(className,base1,base2,base3) \
    INTROSPECTION_BASE_LIST3(className,base1,base2,base3) CLASS_INFO_DEFINITION(className)

#endif


