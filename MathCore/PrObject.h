#pragma once
#include "OdBaseObjectPtr.h"

class OdPrClass;

#define OdPr_DECLARE_MEMBERS_GENERIC(ClassType, ClassName)\
public:                                                                                              \
                                                                                                     \
  /** Casts the specified pointer to an ClassName SmartPointer. **/                      \
  static OdSmartPtr<ClassName> cast(const OdPrObject* pObj)                                          \
  {                                                                                                  \
    if (pObj)                                                                                        \
      return OdSmartPtr<ClassName>(((ClassName*)pObj->queryX(ClassName::desc())), kOdPrObjAttach);   \
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
  virtual OdPrObject* queryX(const OdPrClass* protocolClass) const;                                  \
                                                                                                     \
  /** Creates a new instance of this object type.                   **/                 \
  /** Returns a SmartPointer to the new instance.                       **/                 \
  static OdPrObjectPtr pseudoConstructor();                                                          \
                                                                                                     \
  /** Creates a new instance of this object type.                   **/                 \
  /** Returns a SmartPointer to the new instance.                       **/                 \
   static OdSmartPtr<ClassName> createObject()                                                       \
  { if (!desc()) throw OdError(eNotInitializedYet); return desc()->create(); }

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
        const OdPrObject* pObject)
    {
        if (m_pObject != pObject)  // To prevent reference counter dec/inc which
        {                       // may cause object destruction or subClose
            release();
            m_pObject = (OdPrObject*)pObject;
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
        const OdPrObject* pSource)
        : OdBaseObjectPtr(pSource)
    {
    }

    OdPrObjectPtr(
        const OdPrObject* pSource)
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
        const OdPrObject* pObject) {
        release(); m_pObject = (OdPrObject*)pObject;
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
    OdPrObject* detach()
    {
        OdPrObject* res = m_pObject;
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
        const OdPrObject* source)
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
    OdPrObject* get() { return m_pObject; }
    const OdPrObject* get() const { return m_pObject; }

    /** \details
      Returns the raw pointer to the referenced object.

      \remarks
      The reference counter of the referenced object is not changed.

      \sa
      <link smart_pointers_example_nontypified.html, Example of a Non-Typified Smart Pointer>
    */
    OdPrObject* operator ->() { return m_pObject; }

    const OdPrObject* operator ->() const { return m_pObject; }
    /** \details
      Returns the raw pointer of the referenced object.

      \remarks
      The reference counter of the referenced object is not changed.
    */
    operator OdPrObject* () { return m_pObject; }
    operator const OdPrObject* () const { return m_pObject; }
    bool operator==(
        const OdPrObject* pObject) const {
        return (m_pObject == pObject);
    }
    bool operator!=(
        const OdPrObject* pObject) const {
        return (m_pObject != pObject);
    }
};

/// <summary>
/// This class is the base class for all OdPrObject objects that require Runtime Type Identification.
/// </summary>
class OdPrObject
{
    /// <summary>
    /// Constructor for this class that assigns another Rx - object.
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    OdPrObject(const OdPrObject&) = delete;
    
    /// <summary>
    /// Assignment operator prohibited.
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    OdPrObject& operator = (const OdPrObject&) = delete;

public:
    /// <summary>
    /// Protects derived OdPrObject objects from direct use of new and delete operators
    /// </summary>
    ODPR_HEAP_OPERATORS();

public:
    /** \details
        Default constructor for this class.
    */
    OdPrObject() { }

    /** \details
        The virtual destructor for this class.
    */
    virtual ~OdPrObject();

    /** \details
      Checks whether the object belongs to the specified class and returns a pointer to
      this object if this object can be converted to the specified class.
      \param pClass [in]  Raw pointer to the class describing instance to which the object must be converted.
      \remarks
      If the object cannot be converted, the method returns a Null.
      The program must release this object, if the returned pointer is not Null.
    */
    virtual OdPrObject* queryX(
        const OdPrClass* pClass) const;

    /** \details
     Checks whether the object belongs to the specified class and returns a pointer to
     this object if this object can be converted to the specified class, or throws an exception if it cannot.
      \param pClass [in]  Raw pointer to the class describing instance to which the object must be converted.
      \remarks
      This method generates the eNotThatKindOfClass exception when the object can be not converted to the specified class.
      This method generates the eInvalidInput exception when the argument pClass is Null. This method uses the queryX() method.
    */
    virtual OdPrObject* x(
        const OdPrClass* pClass) const;

    /** \details
      Casts the specified raw pointer to the smart pointer.
      \param pointer [in]  Raw pointer to be cast.
    */
    static OdPrObjectPtr cast(
        const OdPrObject* pointer)
    {
        OdPrObjectPtr pRes;
        if (pointer)
            pRes.attach(pointer->queryX(desc()));
        return pRes;
    }

    /** \details
      Returns the raw pointer to the class describing instance statically associated with this object
      as the OdPrClass object.

      \remarks
      This function is for use only when the class type of this object is known.
      If the class type of this object is unknown, use isA() method instead.

      \sa
      <link rtti_sample_identifying.html, Example of Identifying Classes>

      \sa
      <link rtti_class_functionality.html, Functionality of RTTI>
    */
    static OdPrClass* desc();


    /** \details
      Returns the raw pointer to the class describing instance dynamically associated with this object
      as the OdPrClass object.

      \remarks
      This function is for use only when the class type of this object is unknown.
      If the class type of this object is known, use desc() method instead.

      \sa
      <link rtti_sample_identifying.html, Example of Identifying Classes>

      \sa
      <link rtti_class_functionality.html, Functionality of RTTI>
    */
    virtual OdPrClass* isA() const;

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
    bool isKindOf(const OdPrClass* pClass) const;

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
        const OdPrObject* pSource);

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
        const OdPrObject* pOther) const;

    /** \details
      Returns true if and only if the specified object is equal to this one in a some meaning.
      param pOther [in]  Raw pointer to the object to be compared.
    */
    virtual bool isEqualTo(
        const OdPrObject* pOther) const;
private:
    static OdPrClass* g_pDesc;
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
