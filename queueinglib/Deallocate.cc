//
// This file is part of an OMNeT++/OMNEST simulation example.
//
// Copyright (C) 2006-2008 OpenSim Ltd.
//
// This file is distributed WITHOUT ANY WARRANTY. See the file
// `license' for details on this and other legal matters.
//

#include "Deallocate.h"

namespace queueing {

Define_Module(Deallocate);

void Deallocate::initialize()
{
    obs = 0;
    nObs = par("observation");
    resourceAmount = par("resourceAmount");

    const char *resourceName = par("resourceModuleName");
    cModule *mod = getParentModule()->getModuleByPath(resourceName);
    if (!mod)
        throw cRuntimeError("Cannot find resource pool module `%s'", resourceName);
    resourcePool = check_and_cast<IResourcePool*>(mod);
}

void Deallocate::handleMessage(cMessage *msg)
{
    obs = obs + 1;

    resourcePool->release(resourceAmount);
    send(msg, "out");

    if(obs >= nObs) endSimulation();
}

}; // namespace
