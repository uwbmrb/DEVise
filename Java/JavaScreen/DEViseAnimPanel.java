// ========================================================================
// DEVise Data Visualization Software
// (c) Copyright 1999-2015
// By the DEVise Development Group
// Madison, Wisconsin
// All Rights Reserved.
// ========================================================================

// Under no circumstances is this software to be copied, distributed,
// or altered in any way without prior permission from the DEVise
// Development Group.

// ------------------------------------------------------------------------

// This class forks a thread to use to animate the gears in the corner
// of the JavaScreen.  It does the animation by putting a new GIF onto
// the screen several times a second.

// ------------------------------------------------------------------------

// ========================================================================

// DEViseAnimPanel.java

package JavaScreen;

import  java.awt.*;
import  java.awt.event.*;
import  java.awt.image.*;
import  java.util.*;

// This class represent an animated panel in DEVise
public class DEViseAnimPanel extends Canvas implements Runnable
{
    private jsdevisec jsc = null;

    private Image currentImg = null, offScrImg = null;
    private Vector images = null;
    private Dimension minSize = null;
    private int imageCount = 0, frameNum = 0, activeImageNumber = 1;
    private int imageWidth = 24, imageHeight = 25;
    private Thread animator = null;
    private boolean isAnimated = false;
    private int waitInterval;

    private Date startTime;
    private static final long MIN_WAIT_TIME = 1500; // milliseconds

    public DEViseAnimPanel(jsdevisec what, Vector array, int time)
    {
        jsc = what;

        if (time < 10) {
            waitInterval = 10;
        } else {
            waitInterval = time;
        }

        minSize = new Dimension(imageWidth, imageHeight);

        if (array == null || array.size() < 9) {
            return;
        } else {
            images = array;
            imageCount = 9;
        }

        // all animation symbols must has same size
        currentImg = (Image)images.elementAt(0);
        if (currentImg == null) {
            return;
        }

        imageWidth = currentImg.getWidth(this);
        imageHeight = currentImg.getHeight(this);
        if (imageWidth <= 0 || imageHeight <= 0) {
            return;
        }

        for (int i = 1; i < imageCount; i++)  {
            Image image = (Image)images.elementAt(i);
            if (image == null) {
                return;
            }

            int width = image.getWidth(this);
            int height = image.getHeight(this);
            if (width != imageWidth || height != imageHeight) {
                return;
            }
        }

        minSize = new Dimension(imageWidth, imageHeight);
        isAnimated = true;
    }

    public Dimension getPreferredSize()
    {
        return minSize;
    }

    public Dimension getMinimumSize()
    {
        return minSize;
    }

    public Dimension getMaximumSize()
    {
        return minSize;
    }

    // implement double-buffering, set offScrImg = null if you want to
    // restart double-buffering
    public void update(Graphics g)
    {
        if (offScrImg == null)
            offScrImg = createImage(imageWidth, imageHeight);

        Graphics og = offScrImg.getGraphics();
        paint(og);
        g.drawImage(offScrImg, 0, 0, this);
        og.dispose();
    }

    public void paint(Graphics g)
    {
        if (currentImg != null) {
            g.drawImage(currentImg, 0, 0, this);
        } else {
            g.setColor(jsc.jsValues.uiglobals.bg);
            g.fillRect(0, 0, imageWidth, imageHeight);
        }
    }

    public void run()
    {
        Thread me = Thread.currentThread();
        me.setPriority(Thread.MIN_PRIORITY);

        setActiveImageNumber(1);
        frameNum = 1;

        while (animator == me)  {
            currentImg = (Image)images.elementAt(nextFrame());

            repaint();

            try  {
                Thread.sleep(waitInterval);
            }  catch (InterruptedException e)  {
            }
        }

        if (DEViseGlobals.DEBUG_THREADS >= 1) {
            DEViseUtils.printAllThreads("Thread " + animator + " ending");
        }
    }

    public synchronized void setActiveImageNumber(int number)
    {
        if (number != 1 && number != 5)
            return;

        activeImageNumber = number;
    }

    public synchronized int nextFrame()
    {
        if (activeImageNumber == 1) {
            if (frameNum == 5)
                return (frameNum = 1);
            else
                return frameNum++;
        } else {
            if (frameNum == 9)
                return (frameNum = 5);
            else
                return frameNum++;
        }
    }

    public void start()
    {
        startTime = new Date();

        if (!isAnimated) {
            return;
        }

        if (animator == null) {
            animator = new Thread(this);
            animator.setName("Animator panel");
            animator.start();

            if (DEViseGlobals.DEBUG_THREADS >= 1) {
                DEViseUtils.printAllThreads("Starting thread " + animator);
            }
        }
    }

    public void stop()
    {
        if (startTime != null) {
            Date now = new Date();
            long interval = now.getTime() - startTime.getTime();

            if (interval < jsc.jsValues.uiglobals.minWaitTime) {
                try {
                    Thread.sleep(jsc.jsValues.uiglobals.minWaitTime - interval);
                } catch (InterruptedException ex) {
                    System.err.println("Sleep interrupted: " + ex.toString());
                }
            }

            startTime = null;
        }

        if (!isAnimated) {
            return;
        }

        if (animator == null) {
            return;
        }

        if (animator.isAlive()) {
            if (DEViseGlobals.DEBUG_THREADS >= 1) {
                DEViseUtils.printAllThreads("Stopping thread " + animator);
            }
            animator.stop();
        }

        // animator and currentImg will not be accessed by two thread at the same time,
        // since at this point, the thread animator is already stopped
        animator = null;
        currentImg = (Image)images.elementAt(0);

        repaint();
    }
}
