// ========================================================================
// DEVise Data Visualization Software
// (c) Copyright 1999-2000
// By the DEVise Development Group
// Madison, Wisconsin
// All Rights Reserved.
// ========================================================================

// Under no circumstances is this software to be copied, distributed,
// or altered in any way without prior permission from the DEVise
// Development Group.

// ------------------------------------------------------------------------

// ADD COMMENT: overall description of the function of this class

// ------------------------------------------------------------------------

// $Id$

// $Log$
// Revision 1.6  1999/06/23 20:59:15  wenger
// Added standard DEVise header.
//

// ========================================================================

// DEViseClientDispatcher.java

import java.io.*;
import java.net.*;
import java.util.*;

public class DEViseClientDispatcher implements Runnable
{
    private jspop pop = null;
    private int timestep = 500;

    private Thread dispatcher = null;

    // status = 0, dispatcher is not running
    // status = 1, dispatcher is running
    private boolean status = false;

    public DEViseClientDispatcher(jspop j)
    {
        pop = j;
    }

    private synchronized void setStatus(boolean s)
    {
        status = s;
    }

    public synchronized boolean getStatus()
    {
        return status;
    }

    public void start()
    {
        if (!getStatus()) {
            status = true;
            dispatcher = new Thread(this);
            dispatcher.start();
        }
    }

    public void stop()
    {
        if (getStatus()) {
            if (dispatcher != null) {
                dispatcher.stop();
                dispatcher = null;
            }

            pop.pn("Client dispatcher thread is stopped");
            setStatus(false);
        }
    }

    public void run()
    {
        DEViseClient client = null;
        DEViseServer server = null;

        while (getStatus()) {
            try {
                Thread.sleep(timestep);
            } catch (InterruptedException e) {
            }

            client = pop.getNextRequestingClient();

            if (client != null) {
                server = pop.getNextAvailableServer();
                if (server != null) {
                    server.setCurrentClient(client);
                }
            }
        }

        pop.pn("Client dispatcher thread is stopped");
    }
}


