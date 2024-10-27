#pragma once
#include "OdBaseObjectPtr.h"
#include "OdError.h"
#include <cstdlib>

#define NEW_HANDLER()\
{\
  std::new_handler handler = std::get_new_handler ();\
  if (!handler)\
    throw std::bad_alloc();\
  handler();\
}

#define ODBASE_HEAP_OPERATORS() \
    void* operator new(size_t size) { \
        void* p = std::malloc(size); \
        if (!p) NEW_HANDLER(); \
        return p; \
    } \
    void operator delete(void* p) { \
        std::free(p); \
    } \
    void* operator new[](size_t size) { \
        return std::malloc(size); \
    } \
    void operator delete[](void* p) { \
        std::free(p); \
    } \
    void* operator new(size_t, void* p) { \
        return p; \
    } \
    void operator delete(void*, void*) {} \
    void* operator new[](size_t, void* p) { \
        return p; \
    } \
    void operator delete[](void*, void*) {}

#define ODBASE_DECLARE_MEMBERS_GENERIC(ClassType, ClassName)\
public:                                                                                              \
                                                                                                     \
  /** Casts the specified pointer to an ClassName SmartPointer. **/                      \
  static OdSmartPtr<ClassName> cast(const OdObjectBase* pObj)                                          \
  {                                                                                                  \
    if (pObj)                                                                                        \
      return OdSmartPtr<ClassName>(((ClassName*)pObj->queryX(ClassName::desc())));                   \
    return (ClassName*)0;                                                                            \
  }                                                                                                  \
                                                                                                     \
  static ClassType* g_pDesc;                                                                         \
                                                                                                     \
  /** Returns the static ClassType description object associated with this object. **/  \
  /** This function is for use only when the class type of this object is known.          **/  \
  /** If the class type of this object is unknown, use instead isA().                           **/  \
  static ClassType* desc();                                                                   \
                                                                                                     \
  /** Returns the ClassType description instance associated with this object.      **/  \
  /** This function is for use only when the class type of this object is unknown.        **/  \
  /** If the class type of this object is known, use instead desc().                            **/  \
  virtual ClassType* isA() const;                                                                    \
                                                                                                     \
  /** Returns the Protocol Extension object for this object.        **/                 \
  /** Return null if there is no Protocol Extension object is found.    **/                 \
  virtual OdObjectBase* queryX(const OdClassBase* protocolClass) const;                                  \
                                                                                                     \
  /** Creates a new instance of this object type.                   **/                 \
  /** Returns a SmartPointer to the new instance.                       **/                 \
  static OdPrObjectPtr pseudoConstructor();                                                          \
                                                                                                     \
  /** Creates a new instance of this object type.                   **/                 \
  /** Returns a SmartPointer to the new instance.                       **/                 \
   static OdSmartPtr<ClassName> createObject()                                                       \
  { if (!desc()) throw OdError(eNotInitializedYet); return desc()->create(); }

class OdClassBase;

typedef void (*AppNameChangeFuncPtr)(const OdClassBase* classObj, std::string& newAppName, int saveVer);

/// <summary>
/// Declares the RunTime Type Identification methods required by ODBASEObject objects.
/// 
/// Any class that requires RunTime Type Identification must include this macro in its class declarations,
/// passing its own name.
/// </summary>
#define ODBASE_DECLARE_MEMBERS(ClassName)\
    ODBASE_DECLARE_MEMBERS_GENERIC(OdClassBase, ClassName)

/// <summary>
/// Defines the empty constructor and casts a null pointer for the specified class.
/// </summary>
#define EMPTY_CONSTR(ClassName)(ClassName*)0

/// <summary>
/// Defines the pseudo-constructor for the specified class that creates a new instance, creates a smart pointer to it,
/// does not increment its reference counter, and returns a smart pointer to the instance.
/// The reference counter of a new instance is set to a default value.
/// </summary>
#define NEWOBJ_CONSTR(ClassName) OdSmartPtr<ClassName>(new ClassName, kODBASEObjAttach)

#define ODBASE_DEFINE_RTTI_MEMBERS_GENERIC(ClassType, ClassName, ParentClass) \
                                                                            \
  ClassType* ClassName::g_pDesc = 0;                                        \
  ClassType* ClassName::desc() { return g_pDesc; }                          \
  ClassType* ClassName::isA() const { return g_pDesc; }                     \
                                                                            \
  OdObjectBase* ClassName::queryX(const OdClassBase* pClass) const {            \
    return ::odQueryXImpl<ClassName, ParentClass>(this, pClass);            \
  }

/// <summary>
/// Defines Runtime Type Identification functions for OdObjectBase objects.
/// </summary>
#define ODBASE_DEFINE_RTTI_MEMBERS(ClassName, ParentClass) \
  ODBASE_DEFINE_RTTI_MEMBERS_GENERIC(OdClassBase, ClassName, ParentClass)

/// <summary>
/// Defines the pseudo-constructor for the specified class that creates a new instance, creates a smart pointer to it,
/// does not increment its reference counter, and returns a smart pointer to the instance.
/// The reference counter of a new instance is set to a default value.
/// </summary>
#define ODBASE_DEFINE_PSEUDOCONSTRUCTOR(ClassName,DOCREATE)                                            \
                                                                                                     \
OdPrObjectPtr ClassName::pseudoConstructor() { return OdPrObjectPtr(DOCREATE(ClassName)); }

#define ODBASE_DEFINE_INIT_MEMBERS(ClassName, ParentClass, pseudoConsFn, DwgVer,                \
                                 MaintVer, nProxyFlags, szDWGClassName,                       \
                                 szDxfName, szAppName, nCustomFlags, pMemberCreate, pUserData)\
  ODBASE_DEFINE_RTTI_MEMBERS_GENERIC(                                                           \
      ClassName,                                                                              \
      (::newOdPrClass(szDWGClassName, ParentClass::desc(), pseudoConsFn, DwgVer,              \
        MaintVer, nProxyFlags, szDxfName, szAppName, NULL, nCustomFlags, pMemberCreate, pUserData)),                    \
      (::newOdPrClass(szDWGClassName, ParentClass::desc(), pseudoConsFn, DwgVer,              \
        MaintVer, nProxyFlags, szDxfName, szAppName, pAppNameChangeCallback, nCustomFlags, pMemberCreate, pUserData)))


#define ODBASE_DEFINE_MEMBERS2(ClassName,ParentClass,pseudoConsFn,DwgVer,MaintVer,nProxyFlags,szDWGClassName,szDxfName,szAppName,nCustomFlags) \
                                                                                                     \
ODBASE_DEFINE_RTTI_MEMBERS(ClassName,ParentClass)                                                      \
                                                                                                     \
ODBASE_DEFINE_INIT_MEMBERS(ClassName,ParentClass,pseudoConsFn,                                         \
    DwgVer,MaintVer,nProxyFlags,szDWGClassName,szDxfName,szAppName,nCustomFlags,0,0)

#define ODBASE_DEFINE_MEMBERS(ClassName,ParentClass,DOCREATE,DwgVer,MaintVer,nProxyFlags,szDWGClassName,szDxfName,szAppName)\
                                                                                                     \
ODBASE_DEFINE_MEMBERS2(ClassName,ParentClass,ClassName::pseudoConstructor,                             \
  DwgVer,MaintVer,nProxyFlags,szDWGClassName,szDxfName,szAppName,0)                                  \
                                                                                                     \
ODBASE_DEFINE_PSEUDOCONSTRUCTOR(ClassName,DOCREATE)

#define ODBASE_DEFINE_MEMBERS_EX(ClassName,ParentClass,DOCREATE,DwgVer,MaintVer,nProxyFlags,szDWGClassName,szDxfName,szAppName,nCustomFlags)\
                                                                                                     \
ODBASE_DEFINE_MEMBERS2(ClassName,ParentClass,ClassName::pseudoConstructor,                             \
  DwgVer,MaintVer,nProxyFlags,szDWGClassName,szDxfName,szAppName,nCustomFlags)                       \
                                                                                                     \
ODBASE_DEFINE_PSEUDOCONSTRUCTOR(ClassName,DOCREATE)


#define ODBASE_NO_CONS_DEFINE_MEMBERS_ALTNAME(ClassName,ParentClass,szClassName)                       \
                                                                                                     \
ODBASE_DEFINE_MEMBERS2(ClassName,ParentClass,0,0,0,0,szClassName,std::string::kEmpty,std::string::kEmpty,0)                          \
                                                                                                     \
ODBASE_DEFINE_PSEUDOCONSTRUCTOR(ClassName,EMPTY_CONSTR)

#define ODBASE_NO_CONS_DEFINE_MEMBERS(ClassName,ParentClass)                                           \
                                                                                                     \
ODBASE_NO_CONS_DEFINE_MEMBERS_ALTNAME(ClassName,ParentClass,OD_T(#ClassName))



#define ODBASE_CONS_DEFINE_MEMBERS_ALTNAME(ClassName,ParentClass,szClassName,DOCREATE)                 \
                                                                                                     \
ODBASE_DEFINE_MEMBERS2(ClassName,ParentClass,ClassName::pseudoConstructor,0,0,0,szClassName, "", "",0) \
                                                                                                     \
ODBASE_DEFINE_PSEUDOCONSTRUCTOR(ClassName,DOCREATE)



#define ODBASE_CONS_DEFINE_MEMBERS(ClassName,ParentClass,DOCREATE)                                     \
                                                                                                     \
ODBASE_CONS_DEFINE_MEMBERS_ALTNAME(ClassName,ParentClass,OD_T(#ClassName),DOCREATE)



#define ODBASE_DXF_DEFINE_MEMBERS(ClassName,ParentClass,DOCREATE,DwgVer,MaintVer, nProxyFlags,DxfName,AppName)    \
                                                                                                                \
ODBASE_DEFINE_MEMBERS(ClassName,ParentClass,DOCREATE,                                                             \
    DwgVer,MaintVer,nProxyFlags,OD_T(#ClassName),OD_T(#DxfName),OD_T(#AppName))



#define ODBASE_DXF_CONS_DEFINE_MEMBERS(ClassName,ParentClass,DwgVer,MaintVer,nProxyFlags,DxfName,AppName)    \
                                                                                                           \
ODBASE_DEFINE_MEMBERS2(ClassName,ParentClass,ClassName::pseudoConstructor,                                   \
    DwgVer,MaintVer,nProxyFlags,OD_T(#ClassName),OD_T(#DxfName),OD_T(#AppName),0)                          \
                                                                                                           \
ODBASE_DEFINE_PSEUDOCONSTRUCTOR(ClassName,NEWOBJ_CONSTR)

namespace OdPr
{
    enum Ordering
    {
        kLessThan = -1, // This object < Specified Object
        kEqual = 0, // This object == Specified Object
        kGreaterThan = 1, // This object > Specified Object
        kNotOrderable = 2  // These objects cannot be ordered.
    };
}

class OdPrObjectPtr : public OdBaseObjectPtr
{
    /// <summary>
    /// Increments the reference counter of the referenced object.
    /// </summary>
    inline void internalAddRef();

    /// <summary>
    /// Assigns the pointer of the specified object to the smart pointer.  
    /// The reference counter of the specified object is incremented.
    /// 
    /// If this SmartPointer is currently referencing another object, that object 
    /// is released prior to the assignment.
    /// </summary>
    /// <param name="pObject">Pointer to the specified object to be assigned</param>
    void assign(
        const OdObjectBase* pObject)
    {
        if (m_pObject != pObject)  // To prevent reference counter dec/inc which
        {                       // may cause object destruction or subClose
            release();
            m_pObject = (OdObjectBase*)pObject;
            internalAddRef();
        }
    }
public:
    /** \details
      Constructors for the non-typified smart pointer.

      \param pSource [in]  Pointer to the specified object to be assigned for the new SmartPointer object.

      \remarks
      If pSourceis specified, the smart pointer is set to the address of the specified object. If pSource is not specified, the smart pointer is set to a NULL.

      \remarks
      If OdPrObjMod is specified, the reference counter of the specified object
      is *not* incremented.
    */
    OdPrObjectPtr() : OdBaseObjectPtr() { }

    OdPrObjectPtr(
        const OdObjectBase* pSource)
        : OdBaseObjectPtr(pSource)
    {
        internalAddRef();
    }

    OdPrObjectPtr(
        const OdPrObjectPtr& pSource)
        : OdBaseObjectPtr(pSource.get())
    {
        internalAddRef();
    }

    OdPrObjectPtr(
        const OdBaseObjectPtr& pSource)
        : OdBaseObjectPtr(pSource.get())
    {
        internalAddRef();
    }

    /** \details
      Assigns the pointer of the specifed object to the smart pointer without incrementing its reference counter.

      \param pObject [in]  Pointer to the specified object to be assigned.

      \remarks
      The reference count of the specified object is not incremented.

      If this SmartPointer is currently referencing another object, that object
      is released prior to the assignment.

      \sa
      <link smart_pointers_example_nontypified.html, Example of a Non-Typified Smart Pointer>
    */
    void attach(
        const OdObjectBase* pObject) {
        release(); m_pObject = (OdObjectBase*)pObject;
    }

    /** \details
      Destructor for the non-typified smart pointer.

      \remarks
      Decrements the reference counter of the referenced object. When the reference count reaches zero, the referenced object is deleted.
    */
    ~OdPrObjectPtr()
    {
        release();
    }

    /** \details
      Releases the smart pointer reference to the referenced object.

      \remarks
      Decrements the reference counter of the referenced object.  When the reference count reaches zero,
      the referenced object is deleted. Smart pointer is set to a NULL.

      \sa
      <link smart_pointers_example_nontypified.html, Example of a Non-Typified Smart Pointer>
    */
    inline void release();

    /** \details
      Releases the smart pointer reference to the referenced object without decrementing of the reference counter.

      \returns
      Returns the raw pointer to the referenced object. The reference counter is not modified
      for the referenced object. Smart pointer is set to a NULL.

      \sa
      <link smart_pointers_example_nontypified.html, Example of a Non-Typified Smart Pointer>
    */
    OdObjectBase* detach()
    {
        OdObjectBase* res = m_pObject;
        m_pObject = 0;
        return res;
    }

    /** \remarks
      The assignment operator increments the reference counter of the referenced object and saves its address in the smart pointer.
       If the smart pointer is currently referencing to another object, that assignment operator releases the referenced object prior
       to the assignment.

      \sa
     <link smart_pointers_example_nontypified.html, Example of a Non-Typified Smart Pointer>
    */
    OdPrObjectPtr& operator = (
        const OdPrObjectPtr& source)
    {
        assign(source); return *this;
    }

    OdPrObjectPtr& operator = (
        const OdObjectBase* source)
    {
        assign(source); return *this;
    }

    OdPrObjectPtr& operator = (
        const OdBaseObjectPtr& source)
    {
        assign(source.get()); return *this;
    }

    /** \details
      Returns the raw pointer to the referenced object.

      \remarks
      The smart pointer maintains its reference to the referenced object.
      The reference counter of the referenced object is not changed.

      \sa
      <link smart_pointers_example_nontypified.html, Example of a Non-Typified Smart Pointer>
   */
    OdObjectBase* get() { return m_pObject; }
    const OdObjectBase* get() const { return m_pObject; }

    /** \details
      Returns the raw pointer to the referenced object.

      \remarks
      The reference counter of the referenced object is not changed.

      \sa
      <link smart_pointers_example_nontypified.html, Example of a Non-Typified Smart Pointer>
    */
    OdObjectBase* operator ->() { return m_pObject; }

    const OdObjectBase* operator ->() const { return m_pObject; }
    /** \details
      Returns the raw pointer of the referenced object.

      \remarks
      The reference counter of the referenced object is not changed.
    */
    operator OdObjectBase* () { return m_pObject; }
    operator const OdObjectBase* () const { return m_pObject; }
    bool operator==(
        const OdObjectBase* pObject) const {
        return (m_pObject == pObject);
    }
    bool operator!=(
        const OdObjectBase* pObject) const {
        return (m_pObject != pObject);
    }
};

/// <summary>
/// This class is the base class for all OdObjectBase objects that require Runtime Type Identification.
/// </summary>
class OdObjectBase
{
    /// <summary>
    /// Constructor for this class that assigns another Rx - object.
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    OdObjectBase(const OdObjectBase&) = delete;
    
    /// <summary>
    /// Assignment operator prohibited.
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    OdObjectBase& operator = (const OdObjectBase&) = delete;
    std::string m_objectId = "";
public:
    /// <summary>
    /// Protects derived OdObjectBase objects from direct use of new and delete operators
    /// </summary>
    ODBASE_HEAP_OPERATORS();

public:
    std::string GetObjectId() const;
    static std::string GenerateShortId();
    /** \details
        Default constructor for this class.
    */
    OdObjectBase() { }

    /** \details
        The virtual destructor for this class.
    */
    virtual ~OdObjectBase();

    /** \details
      Checks whether the object belongs to the specified class and returns a pointer to
      this object if this object can be converted to the specified class.
      \param pClass [in]  Raw pointer to the class describing instance to which the object must be converted.
      \remarks
      If the object cannot be converted, the method returns a Null.
      The program must release this object, if the returned pointer is not Null.
    */
    virtual OdObjectBase* queryX(
        const OdClassBase* pClass) const;

    /** \details
     Checks whether the object belongs to the specified class and returns a pointer to
     this object if this object can be converted to the specified class, or throws an exception if it cannot.
      \param pClass [in]  Raw pointer to the class describing instance to which the object must be converted.
      \remarks
      This method generates the eNotThatKindOfClass exception when the object can be not converted to the specified class.
      This method generates the eInvalidInput exception when the argument pClass is Null. This method uses the queryX() method.
    */
    virtual OdObjectBase* x(
        const OdClassBase* pClass) const;

    /** \details
      Casts the specified raw pointer to the smart pointer.
      \param pointer [in]  Raw pointer to be cast.
    */
    static OdPrObjectPtr cast(
        const OdObjectBase* pointer)
    {
        OdPrObjectPtr pRes;
        if (pointer)
            pRes.attach(pointer->queryX(desc()));
        return pRes;
    }

    /** \details
      Returns the raw pointer to the class describing instance statically associated with this object
      as the OdClassBase object.

      \remarks
      This function is for use only when the class type of this object is known.
      If the class type of this object is unknown, use isA() method instead.

      \sa
      <link rtti_sample_identifying.html, Example of Identifying Classes>

      \sa
      <link rtti_class_functionality.html, Functionality of RTTI>
    */
    static OdClassBase* desc();


    /** \details
      Returns the raw pointer to the class describing instance dynamically associated with this object
      as the OdClassBase object.

      \remarks
      This function is for use only when the class type of this object is unknown.
      If the class type of this object is known, use desc() method instead.

      \sa
      <link rtti_sample_identifying.html, Example of Identifying Classes>

      \sa
      <link rtti_class_functionality.html, Functionality of RTTI>
    */
    virtual OdClassBase* isA() const;

    /** \details
      Declares the method incrementing the reference counter in objects derived from this class.

      \remarks
      It is the pure virtual method that does not have an implementation. You must redefine it in the derived class.

      \sa
      <link smart_pointers_overview.html, Overview of Smart Pointer Classes>
    */
    virtual void addRef() = 0;

    /** \details
      Declares the method decrementing the reference counter in objects derived from this class.

      \remarks
      It is the pure virtual method that does not have an implementation. You must redefine it in the derived class.

      \sa
      <link smart_pointers_overview.html, Overview of Smart Pointer Classes>
    */
    virtual void release() = 0;

    /** \details
      Returns the value of the reference counter, that is, the number of references to an instance of this class.

      \remarks
      This method has the default implementation that returns 1. You shloud redefine it in the derived class.

      \sa
      <link smart_pointers_overview.html, Overview of Smart Pointer Classes>
    */
    virtual long numRefs() const;

    /** \details
     Checks whether the object belongs to the specified class and
     returns true if and only if this object is an instance of the specified class or
     a subclass of the specified class.

      \param pClass [in]  Raw pointer to the class describing instance to be checked.

      \sa
      <link rtti_sample_belonging.html, Example of Belonging to an Instance of a Class>

      \sa
      <link rtti_class_belonging.html, Belonging to an Instance of a Class>
   */
    bool isKindOf(const OdClassBase* pClass) const;

    /** \details
      Creates a *clone* of this object, and returns a pointer to the *clone*.
    */
    virtual OdPrObjectPtr clone() const;

    /** details
      Copies the contents of the specified object into this object.
      \param pSource [in] Pointer to the source object.
      \remarks
      The default implementation of this function does nothing but throw an eNotApplicable exception.
      Throws:
      eNotApplicable Exception
   */
    virtual void copyFrom(
        const OdObjectBase* pSource);

    /** \details
      Compares another object to this one in a some meaning.

      \param pOther [in]  Raw pointer to the object to be compared.

      \remarks
      This method returns one of the following:

      <table>
      Name             Value    Description
      _kLessThan_     -1       This object < Other Object.
      _kEqual_              0       This object = Other Object.
      _kGreaterThan_     1       This object > Other Object.
      _kNotOrderable_     2       This class is not orderable.
      </table>
      \remarks
      The default implementation of this method returns _kNotOrderable_.
    */
    virtual OdPr::Ordering comparedTo(
        const OdObjectBase* pOther) const;

    /** \details
      Returns true if and only if the specified object is equal to this one in a some meaning.
      param pOther [in]  Raw pointer to the object to be compared.
    */
    virtual bool isEqualTo(
        const OdObjectBase* pOther) const;
private:
    static OdClassBase* g_pDesc;
};

void OdPrObjectPtr::internalAddRef()
{
    if (m_pObject) { m_pObject->addRef(); }
}
void OdPrObjectPtr::release()
{
    if (m_pObject)
    {
        m_pObject->release();
        m_pObject = NULL;
    }
}

#include "OdSmartPtr.h"
class OdPrOverruleIterator;
class OdBaseAttributeCollection;
typedef OdPrObjectPtr(*OdPseudoConstructorType)();
class OdClassBaseImpl;

class OdClassBase : public OdObjectBase
{
    friend class OdClassBaseImpl;

protected:
    OdClassBaseImpl* m_pImpl;
    OdClassBase(OdClassBaseImpl*);
public:
    ODBASE_DECLARE_MEMBERS(OdClassBase);
    OdClassBase();
    ~OdClassBase();

    /** \details
      Creates the Protocol Extension for the specified OdClassBase.

      \param pProtocolClass [in]  Pointer to the Protocol Extension class.
      \param pProtocolObject [in]  Pointer to the Protocol Extension Object.

      \returns
      Returns a SmartPointer to the Protocol Extension.

      \remarks
      The default implementation of  this object does nothing but return a
      null pointer, and asserts in debug mode. It will be
      fully implemented in a future *release*.
    */
    OdPrObjectPtr addX(
        OdClassBase* pProtocolClass,
        OdObjectBase* pProtocolObject);

    /** \details
      Returns the Protocol Extension for the specified
      Protocol extension class.

      \param pProtocolClass [in]  Pointer to the Protocol Extension class.

      \returns
      Returns a SmartPointer to the Protocol Extension.

      \remarks
      The default implementation of this object does nothing but
      assert in debug mode, and return a null pointer.
      It will be fully implemented in a future *release*.
    */
    OdPrObjectPtr getX(
        const OdClassBase* pProtocolClass);

    /** \details
      Deletes the Protocol Extension for the specified Protocol Extension class.

      \returns
      Returns the Protocol Extension Object.

      \param pProtocolClass [in]  Pointer to the Protocol Extension class.

      \remarks
      As currently implemented, this function does nothing but
      assert in debug mode, and return a null pointer.
      It will be fully implemented in a future *release*.
    */
    OdPrObjectPtr delX(
        OdClassBase* pProtocolClass);

    /** \details
      Creates a new instance of the class associated with the class describing instance
      using the pseudo-constructor of the class.

      \returns
      Returns a smart pointer to the newly created instance.
    */
    virtual OdPrObjectPtr create() const;

    /** \details
      Returns the application class name for the class describing instance represented by this
      OdClassBase object. Custom class can alter its application name depending on file format version
      it's being saved to.
    */
    const std::string appName() const;

    /** \details
      Returns a pointer to the callback function which is called when a drawing is to be saved and
      the logical application class name represented by the class description instance to be written
      out to file for the custom class, or NULL, if the callback function is not assigned.
    */
    AppNameChangeFuncPtr appNameCallbackPtr() const;

    /** \details
      Returns the DXF class name for the class describing instance represented by this OdClassBase object.
    */
    const std::string dxfName() const;

    /** \details
      Returns the class name for the class describing instance represented by this OdClassBase object.
    */
    const std::string name() const;
    /** \details
      Returns the /proxy flags/ for the class describing instance represented by this OdClassBase object.
    */
    OdUInt32 proxyFlags() const;

    /** \details
     Checks whether the class defined by this class describing instance belongs to or
     derived from the specified class. The method returns true if and only if this object is
     an instance of the specified class or a subclass of the specified class.

      \param pClass [in]  Raw pointer to the class describing instance to be checked.
    */
    virtual bool isDerivedFrom(
        const OdClassBase* pClass) const;

    /** \details
      Returns the raw pointer to the class describing instance which describes
      the parent class for this class as the OdClassBase object.
    **/
    OdClassBase* myParent() const;

    /** \details
      Returns the raw pointer to the function that is the pseudo-constructor for this class.
    **/
    OdPseudoConstructorType constructor();

    /** \details
      Sets the user-defined function as the pseudo-constructor for this class.

      \param pseudoConstr [in]  Raw pointer to the user-defined function that does not have arguments
      and returns the smart pointer to a new instance of this class.
    **/
    void setConstructor(
        OdPseudoConstructorType psuedoConstr);

    /** \details
      Returns the custom flags for the class describing instance represented by this OdClassBase object.
    */
    OdUInt32 customFlags() const;
    const OdBaseAttributeCollection& attributes() const;
    OdBaseAttributeCollection& attributes();
};

typedef OdSmartPtr<OdClassBase> OdPrClassPtr;

inline bool OdObjectBase::isKindOf(const OdClassBase* pClass) const {
    //isKindOf() not working with react wich has multiple inheritance of parent
    //return isA()->isDerivedFrom(pClass);
    if (isA() && isA()->isDerivedFrom(pClass))
    {
        return true;
    }

    OdPrObjectPtr pRes;
    pRes.attach(queryX(pClass));
    return (!pRes.isNull());
}

template <class Class, class Parent>
OdObjectBase* odQueryXImpl(const Class* pThis, const OdClassBase* pClass)
{
    OdObjectBase* pObj = 0;
    if (!pClass) // requested class is not registred
        return pObj;
    if (pClass == Class::desc())
    {
        pObj = (OdObjectBase*)pThis;
        pObj->addRef();
    }
    else
    {
        pObj = Class::desc()->getX(pClass).detach();
        if (!pObj)
            pObj = pThis->Parent::queryX(pClass);
    }
    return pObj;
}