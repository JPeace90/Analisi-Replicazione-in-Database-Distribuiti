//
// This file is part of an OMNeT++/OMNEST simulation example.
//
// Copyright (C) 2006-2008 OpenSim Ltd.
//
// This file is distributed WITHOUT ANY WARRANTY. See the file
// `license' for details on this and other legal matters.
//

#include "Source.h"
#include "Job.h"

namespace queueing {


void SourceBase::initialize()
{
    createdSignal = registerSignal("created");
    jobCounter = 0;
    WATCH(jobCounter);
    jobName = par("jobName").stringValue();
    if (jobName == "")
        jobName = getName();

}

Job *SourceBase::createJob()
{
    /* Nostro codice */
    //srand(time(NULL));
    int casual = intuniform(1,10,0);//rand()% 10+1;



    if(casual >= 1 && casual <= 6){
        jobName = "Read";
    }
    else jobName = "Updating";

    /* ------------------------------------ */
    char buf[80];
    sprintf(buf, "%.60s-%d", jobName.c_str(), ++jobCounter);
    Job *job = new Job(buf);
    job->setKind(par("jobType"));
    job->setPriority(par("jobPriority"));
    generateData(job);

    cDisplayString jobString = job->getDisplayString();

    if(strncmp(job->getName(), "Read", 4)==0){
        jobString.parse("b=10,10,oval,blue");
        job->setType(0);
    }
    else {
        jobString.parse("b=10,10,rect,red");
        job->setType(1);
    }
    job->setDisplayString(jobString);

    return job;
}

void SourceBase::generateData(Job *job){
    //srand(time(NULL));
    int casual = intuniform(1,16,0);

    //std::cout << "Value: " << casual << endl;

    job->setValue(casual);
}

void SourceBase::finish()
{
    emit(createdSignal, jobCounter);
}

//----

Define_Module(Source);

void Source::initialize()
{
    SourceBase::initialize();
    startTime = par("startTime");
    stopTime = par("stopTime");
    numJobs = par("numJobs");

    // schedule the first message timer for start time
    scheduleAt(startTime, new cMessage("newJobTimer"));
}

void Source::handleMessage(cMessage *msg)
{
    ASSERT(msg->isSelfMessage());

    if ((numJobs < 0 || numJobs > jobCounter) && (stopTime < 0 || stopTime > simTime()))
    {
        // reschedule the timer for the next message
        scheduleAt(simTime() + par("interArrivalTime").doubleValue(), msg);

        Job *job = createJob();
        send(job, "out");
    }
    else
    {
        // finished
        delete msg;
    }
}



//----

Define_Module(SourceOnce);

void SourceOnce::initialize()
{
    SourceBase::initialize();
    simtime_t time = par("time");
    scheduleAt(time, new cMessage("newJobTimer"));
}

void SourceOnce::handleMessage(cMessage *msg)
{
    ASSERT(msg->isSelfMessage());
    delete msg;

    int n = par("numJobs");
    for (int i=0; i<n; i++)
    {
        Job *job = createJob();
        send(job, "out");
    }
}

}; //namespace

