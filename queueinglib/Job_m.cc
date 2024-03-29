//
// Generated file, do not edit! Created by opp_msgc 4.5 from Job.msg.
//

// Disable warnings about unused variables, empty switch stmts, etc:
#ifdef _MSC_VER
#  pragma warning(disable:4101)
#  pragma warning(disable:4065)
#endif

#include <iostream>
#include <sstream>
#include "Job_m.h"

USING_NAMESPACE


// Another default rule (prevents compiler from choosing base class' doPacking())
template<typename T>
void doPacking(cCommBuffer *, T& t) {
    throw cRuntimeError("Parsim error: no doPacking() function for type %s or its base class (check .msg and _m.cc/h files!)",opp_typename(typeid(t)));
}

template<typename T>
void doUnpacking(cCommBuffer *, T& t) {
    throw cRuntimeError("Parsim error: no doUnpacking() function for type %s or its base class (check .msg and _m.cc/h files!)",opp_typename(typeid(t)));
}



namespace queueing {

// Template rule for outputting std::vector<T> types
template<typename T, typename A>
inline std::ostream& operator<<(std::ostream& out, const std::vector<T,A>& vec)
{
    out.put('{');
    for(typename std::vector<T,A>::const_iterator it = vec.begin(); it != vec.end(); ++it)
    {
        if (it != vec.begin()) {
            out.put(','); out.put(' ');
        }
        out << *it;
    }
    out.put('}');
    
    char buf[32];
    sprintf(buf, " (size=%u)", (unsigned int)vec.size());
    out.write(buf, strlen(buf));
    return out;
}

// Template rule which fires if a struct or class doesn't have operator<<
template<typename T>
inline std::ostream& operator<<(std::ostream& out,const T&) {return out;}

Job_Base::Job_Base(const char *name, int kind) : ::cMessage(name,kind)
{
    this->displayString_var = "b=5,5,rect,white,kind,5";
    this->time_var = 0;
    this->value_var = 0;
    this->type_var = 0;
    this->locks_var = 0;
    this->priority_var = 0;
    this->totalQueueingTime_var = 0;
    this->totalServiceTime_var = 0;
    this->totalDelayTime_var = 0;
    this->queueCount_var = 0;
    this->delayCount_var = 0;
    this->generation_var = 0;
}

Job_Base::Job_Base(const Job_Base& other) : ::cMessage(other)
{
    copy(other);
}

Job_Base::~Job_Base()
{
}

Job_Base& Job_Base::operator=(const Job_Base& other)
{
    if (this==&other) return *this;
    ::cMessage::operator=(other);
    copy(other);
    return *this;
}

void Job_Base::copy(const Job_Base& other)
{
    this->displayString_var = other.displayString_var;
    this->time_var = other.time_var;
    this->value_var = other.value_var;
    this->type_var = other.type_var;
    this->locks_var = other.locks_var;
    this->priority_var = other.priority_var;
    this->totalQueueingTime_var = other.totalQueueingTime_var;
    this->totalServiceTime_var = other.totalServiceTime_var;
    this->totalDelayTime_var = other.totalDelayTime_var;
    this->queueCount_var = other.queueCount_var;
    this->delayCount_var = other.delayCount_var;
    this->generation_var = other.generation_var;
}

void Job_Base::parsimPack(cCommBuffer *b)
{
    ::cMessage::parsimPack(b);
    doPacking(b,this->displayString_var);
    doPacking(b,this->time_var);
    doPacking(b,this->value_var);
    doPacking(b,this->type_var);
    doPacking(b,this->locks_var);
    doPacking(b,this->priority_var);
    doPacking(b,this->totalQueueingTime_var);
    doPacking(b,this->totalServiceTime_var);
    doPacking(b,this->totalDelayTime_var);
    doPacking(b,this->queueCount_var);
    doPacking(b,this->delayCount_var);
    doPacking(b,this->generation_var);
}

void Job_Base::parsimUnpack(cCommBuffer *b)
{
    ::cMessage::parsimUnpack(b);
    doUnpacking(b,this->displayString_var);
    doUnpacking(b,this->time_var);
    doUnpacking(b,this->value_var);
    doUnpacking(b,this->type_var);
    doUnpacking(b,this->locks_var);
    doUnpacking(b,this->priority_var);
    doUnpacking(b,this->totalQueueingTime_var);
    doUnpacking(b,this->totalServiceTime_var);
    doUnpacking(b,this->totalDelayTime_var);
    doUnpacking(b,this->queueCount_var);
    doUnpacking(b,this->delayCount_var);
    doUnpacking(b,this->generation_var);
}

const char * Job_Base::getDisplayString() const
{
    return displayString_var.c_str();
}

void Job_Base::setDisplayString(const char * displayString)
{
    this->displayString_var = displayString;
}

simtime_t Job_Base::getTime() const
{
    return time_var;
}

void Job_Base::setTime(simtime_t time)
{
    this->time_var = time;
}

int Job_Base::getValue() const
{
    return value_var;
}

void Job_Base::setValue(int value)
{
    this->value_var = value;
}

int Job_Base::getType() const
{
    return type_var;
}

void Job_Base::setType(int type)
{
    this->type_var = type;
}

bool Job_Base::getLocks() const
{
    return locks_var;
}

void Job_Base::setLocks(bool locks)
{
    this->locks_var = locks;
}

int Job_Base::getPriority() const
{
    return priority_var;
}

void Job_Base::setPriority(int priority)
{
    this->priority_var = priority;
}

simtime_t Job_Base::getTotalQueueingTime() const
{
    return totalQueueingTime_var;
}

void Job_Base::setTotalQueueingTime(simtime_t totalQueueingTime)
{
    this->totalQueueingTime_var = totalQueueingTime;
}

simtime_t Job_Base::getTotalServiceTime() const
{
    return totalServiceTime_var;
}

void Job_Base::setTotalServiceTime(simtime_t totalServiceTime)
{
    this->totalServiceTime_var = totalServiceTime;
}

simtime_t Job_Base::getTotalDelayTime() const
{
    return totalDelayTime_var;
}

void Job_Base::setTotalDelayTime(simtime_t totalDelayTime)
{
    this->totalDelayTime_var = totalDelayTime;
}

int Job_Base::getQueueCount() const
{
    return queueCount_var;
}

void Job_Base::setQueueCount(int queueCount)
{
    this->queueCount_var = queueCount;
}

int Job_Base::getDelayCount() const
{
    return delayCount_var;
}

void Job_Base::setDelayCount(int delayCount)
{
    this->delayCount_var = delayCount;
}

int Job_Base::getGeneration() const
{
    return generation_var;
}

void Job_Base::setGeneration(int generation)
{
    this->generation_var = generation;
}

class JobDescriptor : public cClassDescriptor
{
  public:
    JobDescriptor();
    virtual ~JobDescriptor();

    virtual bool doesSupport(cObject *obj) const;
    virtual const char *getProperty(const char *propertyname) const;
    virtual int getFieldCount(void *object) const;
    virtual const char *getFieldName(void *object, int field) const;
    virtual int findField(void *object, const char *fieldName) const;
    virtual unsigned int getFieldTypeFlags(void *object, int field) const;
    virtual const char *getFieldTypeString(void *object, int field) const;
    virtual const char *getFieldProperty(void *object, int field, const char *propertyname) const;
    virtual int getArraySize(void *object, int field) const;

    virtual std::string getFieldAsString(void *object, int field, int i) const;
    virtual bool setFieldAsString(void *object, int field, int i, const char *value) const;

    virtual const char *getFieldStructName(void *object, int field) const;
    virtual void *getFieldStructPointer(void *object, int field, int i) const;
};

Register_ClassDescriptor(JobDescriptor);

JobDescriptor::JobDescriptor() : cClassDescriptor("queueing::Job", "cMessage")
{
}

JobDescriptor::~JobDescriptor()
{
}

bool JobDescriptor::doesSupport(cObject *obj) const
{
    return dynamic_cast<Job_Base *>(obj)!=NULL;
}

const char *JobDescriptor::getProperty(const char *propertyname) const
{
    if (!strcmp(propertyname,"customize")) return "true";
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : NULL;
}

int JobDescriptor::getFieldCount(void *object) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 12+basedesc->getFieldCount(object) : 12;
}

unsigned int JobDescriptor::getFieldTypeFlags(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldTypeFlags(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
    };
    return (field>=0 && field<12) ? fieldTypeFlags[field] : 0;
}

const char *JobDescriptor::getFieldName(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldNames[] = {
        "displayString",
        "time",
        "value",
        "type",
        "locks",
        "priority",
        "totalQueueingTime",
        "totalServiceTime",
        "totalDelayTime",
        "queueCount",
        "delayCount",
        "generation",
    };
    return (field>=0 && field<12) ? fieldNames[field] : NULL;
}

int JobDescriptor::findField(void *object, const char *fieldName) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount(object) : 0;
    if (fieldName[0]=='d' && strcmp(fieldName, "displayString")==0) return base+0;
    if (fieldName[0]=='t' && strcmp(fieldName, "time")==0) return base+1;
    if (fieldName[0]=='v' && strcmp(fieldName, "value")==0) return base+2;
    if (fieldName[0]=='t' && strcmp(fieldName, "type")==0) return base+3;
    if (fieldName[0]=='l' && strcmp(fieldName, "locks")==0) return base+4;
    if (fieldName[0]=='p' && strcmp(fieldName, "priority")==0) return base+5;
    if (fieldName[0]=='t' && strcmp(fieldName, "totalQueueingTime")==0) return base+6;
    if (fieldName[0]=='t' && strcmp(fieldName, "totalServiceTime")==0) return base+7;
    if (fieldName[0]=='t' && strcmp(fieldName, "totalDelayTime")==0) return base+8;
    if (fieldName[0]=='q' && strcmp(fieldName, "queueCount")==0) return base+9;
    if (fieldName[0]=='d' && strcmp(fieldName, "delayCount")==0) return base+10;
    if (fieldName[0]=='g' && strcmp(fieldName, "generation")==0) return base+11;
    return basedesc ? basedesc->findField(object, fieldName) : -1;
}

const char *JobDescriptor::getFieldTypeString(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldTypeString(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldTypeStrings[] = {
        "string",
        "simtime_t",
        "int",
        "int",
        "bool",
        "int",
        "simtime_t",
        "simtime_t",
        "simtime_t",
        "int",
        "int",
        "int",
    };
    return (field>=0 && field<12) ? fieldTypeStrings[field] : NULL;
}

const char *JobDescriptor::getFieldProperty(void *object, int field, const char *propertyname) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldProperty(object, field, propertyname);
        field -= basedesc->getFieldCount(object);
    }
    switch (field) {
        default: return NULL;
    }
}

int JobDescriptor::getArraySize(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getArraySize(object, field);
        field -= basedesc->getFieldCount(object);
    }
    Job_Base *pp = (Job_Base *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

std::string JobDescriptor::getFieldAsString(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldAsString(object,field,i);
        field -= basedesc->getFieldCount(object);
    }
    Job_Base *pp = (Job_Base *)object; (void)pp;
    switch (field) {
        case 0: return oppstring2string(pp->getDisplayString());
        case 1: return double2string(pp->getTime());
        case 2: return long2string(pp->getValue());
        case 3: return long2string(pp->getType());
        case 4: return bool2string(pp->getLocks());
        case 5: return long2string(pp->getPriority());
        case 6: return double2string(pp->getTotalQueueingTime());
        case 7: return double2string(pp->getTotalServiceTime());
        case 8: return double2string(pp->getTotalDelayTime());
        case 9: return long2string(pp->getQueueCount());
        case 10: return long2string(pp->getDelayCount());
        case 11: return long2string(pp->getGeneration());
        default: return "";
    }
}

bool JobDescriptor::setFieldAsString(void *object, int field, int i, const char *value) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->setFieldAsString(object,field,i,value);
        field -= basedesc->getFieldCount(object);
    }
    Job_Base *pp = (Job_Base *)object; (void)pp;
    switch (field) {
        case 0: pp->setDisplayString((value)); return true;
        case 1: pp->setTime(string2double(value)); return true;
        case 2: pp->setValue(string2long(value)); return true;
        case 3: pp->setType(string2long(value)); return true;
        case 4: pp->setLocks(string2bool(value)); return true;
        case 5: pp->setPriority(string2long(value)); return true;
        case 6: pp->setTotalQueueingTime(string2double(value)); return true;
        case 7: pp->setTotalServiceTime(string2double(value)); return true;
        case 8: pp->setTotalDelayTime(string2double(value)); return true;
        case 9: pp->setQueueCount(string2long(value)); return true;
        case 10: pp->setDelayCount(string2long(value)); return true;
        case 11: pp->setGeneration(string2long(value)); return true;
        default: return false;
    }
}

const char *JobDescriptor::getFieldStructName(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    switch (field) {
        default: return NULL;
    };
}

void *JobDescriptor::getFieldStructPointer(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructPointer(object, field, i);
        field -= basedesc->getFieldCount(object);
    }
    Job_Base *pp = (Job_Base *)object; (void)pp;
    switch (field) {
        default: return NULL;
    }
}

}; // end namespace queueing

