// ========================================================================
// DEVise Data Visualization Software
// (c) Copyright 1999
// By the DEVise Development Group
// Madison, Wisconsin
// All Rights Reserved.
// ========================================================================

// Under no circumstances is this software to be copied, distributed,
// or altered in any way without prior permission from the DEVise
// Development Group.

// $Id$

// $Log$
// Revision 1.52  1999/10/10 09:51:01  hongyu
// *** empty log message ***
//
// Revision 1.51  1999/10/10 08:49:54  hongyu
// Major changes to JAVAScreen have been commited in this update, including:
// 1. restructure of JavaScreen internal structure to adapt to vast changes
//    in DEVise and also prepare to future upgrade
// 2. Fix a number of bugs in visualization and user interaction
// 3. Add a number of new features in visualization and user interaction
// 4. Add support for complicated 3D molecular view
//
// Revision 1.50  1999/08/03 05:56:50  hongyu
// bug fixes    by Hongyu Yao
//
// Revision 1.49  1999/07/27 17:11:19  hongyu
// *** empty log message ***
//
// Revision 1.47  1999/06/23 20:59:21  wenger
// Added standard DEVise header.
//

// ========================================================================

// jsdevisec.java

import  java.awt.*;
import  java.io.*;
import  java.net.*;
import  java.awt.event.*;
import  java.util.*;

public class jsdevisec extends Panel
{
    private YLogGUI debugWindow = null;
    private int debugLevel = 0;

    public DEViseCmdDispatcher dispatcher = null;

    public Frame parentFrame = null;
    private boolean isCenterScreen = false;
    //public Applet parentApplet = null;

    public DEViseScreen jscreen = null;

    private Button openButton = new Button("Open");
    private Button closeButton = new Button("Close");
    public  Button stopButton = new Button("Stop");
    private Button restartButton = new Button("Restart");
    //private Button statButton = new Button("Stats");
    private Button setButton = new Button("Option");
    private Button exitButton = new Button("Exit");

    public DEViseAnimPanel animPanel = null;
    public DEViseViewInfo viewInfo = null;
    public DEViseTrafficLight light = null;

    private YMsgBox msgbox = null;

    public SessionDlg sessiondlg = null;
    private RecordDlg recorddlg = null;
    private ServerStateDlg statedlg = null;
    private SettingDlg settingdlg = null;

    public boolean isSessionOpened = false;
    private boolean isQuit = false;
    public int stopNumber = 0;

    public boolean isShowProgramInfo = false;
    public String rootDir = "DEViseSession";
    public String currentDir = "DEViseSession";
    public String currentSession = null;

    public Cursor lastCursor = DEViseGlobals.defaultCursor;


    public jsdevisec(Frame frame, Vector images, int level, String sessionName)
    {
        // frame might be null if JavaScreen is running inside a browser
        parentFrame = frame;
        if (parentFrame == null) {
            parentFrame = new Frame();
            isCenterScreen = true;
        }

        debugLevel = level;
        if (debugLevel > 0) {
            debugWindow = new YLogGUI(debugLevel);
        }

        // determine the font size according to JavaScreen size
        int width = DEViseGlobals.maxScreenSize.width;
        int height = DEViseGlobals.maxScreenSize.height;

        if (width > 800 ) {
            DEViseGlobals.font = new Font("Serif", Font.PLAIN, 12);
            DEViseGlobals.textFont = new Font("Serif", Font.PLAIN, 12);
        } else if (width <= 800 && width > 640) {
            DEViseGlobals.font = new Font("Serif", Font.PLAIN, 10);
            DEViseGlobals.textFont = new Font("Serif", Font.PLAIN, 10);
        } else if (width <= 640) {
            DEViseGlobals.font = new Font("Serif", Font.PLAIN, 8);
            DEViseGlobals.textFont = new Font("Serif", Font.PLAIN, 8);
        }

        setBackground(DEViseGlobals.bg);
        setForeground(DEViseGlobals.fg);
        setFont(DEViseGlobals.font);
        setLayout(new BorderLayout(2, 2));

        Panel topPanel = new Panel(new BorderLayout(2, 2));
        Panel mainPanel = new Panel(new FlowLayout(FlowLayout.LEFT, 2, 2));

        animPanel = new DEViseAnimPanel(this, images, 100);

        mainPanel.add(animPanel);

        if (images != null && images.size() == 11) {
            try {
                light = new DEViseTrafficLight((Image)images.elementAt(9), (Image)images.elementAt(10), "0");
            } catch (YException e) {
                light = null;
            }
        }

        if (light != null) {
            mainPanel.add(light);
        }

        Component[] button = null;
        if (DEViseGlobals.inBrowser) {
            button = new Component[2];
            button[0] = restartButton;
            button[1] = stopButton;
        } else {
            button = new Component[6];
            button[0] = openButton;
            button[1] = closeButton;
            button[2] = stopButton;
            button[3] = restartButton;
            button[4] = setButton;
            button[5] = exitButton;
        }

        DEViseComponentPanel buttonPanel = new DEViseComponentPanel(button, "Horizontal", 5, 1);

        mainPanel.add(buttonPanel);

        viewInfo = new DEViseViewInfo(this, images);

        topPanel.add(mainPanel, BorderLayout.WEST);
        topPanel.add(viewInfo, BorderLayout.EAST);

        if (DEViseGlobals.inBrowser) {
            topPanel.setFont(new Font("Serif", Font.PLAIN, 14));
            topPanel.add(new Label("                       " + DEViseGlobals.javaScreenTitle), BorderLayout.CENTER);
        }

        if (DEViseGlobals.screenSize.width <= 0) {
            DEViseGlobals.screenSize.width = DEViseGlobals.maxScreenSize.width;
        } else if (DEViseGlobals.screenSize.width < DEViseGlobals.minScreenSize.width && DEViseGlobals.screenSize.width > 0) {
            DEViseGlobals.screenSize.width = DEViseGlobals.minScreenSize.width;
        } else if (DEViseGlobals.screenSize.width > DEViseGlobals.maxScreenSize.width) {
            DEViseGlobals.screenSize.width = DEViseGlobals.maxScreenSize.width;
        }

        if (DEViseGlobals.screenSize.height <= 0) {
            DEViseGlobals.screenSize.height = DEViseGlobals.maxScreenSize.height;
        } else if (DEViseGlobals.screenSize.height < DEViseGlobals.minScreenSize.height && DEViseGlobals.screenSize.height > 0) {
            DEViseGlobals.screenSize.height = DEViseGlobals.minScreenSize.height;
        } else if (DEViseGlobals.screenSize.height > DEViseGlobals.maxScreenSize.height) {
            DEViseGlobals.screenSize.height = DEViseGlobals.maxScreenSize.height;
        }

        jscreen = new DEViseScreen(this);
        Panel screenPanel = new Panel(new FlowLayout(FlowLayout.CENTER, 3, 3));
        //int r = DEViseGlobals.bg.getRed() + 32, g = DEViseGlobals.bg.getGreen() + 32, b = DEViseGlobals.bg.getBlue() + 32;
        //if (r > 255) r = 255;
        //if (g > 255) g = 255;
        //if (b > 255) b = 255;
        //screenPanel.setBackground(new Color(r, g, b));
        screenPanel.setBackground(new Color(64, 192, 0));
        screenPanel.add(jscreen);

        add(topPanel, BorderLayout.NORTH);
        add(screenPanel, BorderLayout.CENTER);

        // define event handler for buttons
        openButton.addActionListener(new ActionListener()
                {
                    public void actionPerformed(ActionEvent event)
                    {
                        if (isSessionOpened) {
                            showMsg("You already have a session opened!\nPlease close current session first!");
                            return;
                        }

                        dispatcher.start("JAVAC_GetSessionList {" + currentDir + "}");
                    }
                });
        closeButton.addActionListener(new ActionListener()
                {
                    public void actionPerformed(ActionEvent event)
                    {
                        if (!isSessionOpened) {
                            showMsg("You do not have any opened session!");
                            return;
                        }

                        dispatcher.start("JAVAC_CloseCurrentSession");
                    }
                });
        stopButton.addActionListener(new ActionListener()
                {
                    public void actionPerformed(ActionEvent event)
                    {
                        if (dispatcher.getStatus() != 0) {
                            stopNumber++;
                            if (stopNumber > 1) {
                                dispatcher.stop(true, false);
                            } else {
                                dispatcher.stop();
                            }
                        }
                    }
                });
        restartButton.addActionListener(new ActionListener()
                {
                    public void actionPerformed(ActionEvent event)
                    {
                        if (!isSessionOpened) {
                            showMsg("You do not have any opened session!");
                            return;
                        }

                        dispatcher.start("JAVAC_OpenSession {" + currentDir + "/" + currentSession + "}");
                    }
                });
        setButton.addActionListener(new ActionListener()
                {
                    public void actionPerformed(ActionEvent event)
                    {
                        showSetting();
                    }
                });
        exitButton.addActionListener(new ActionListener()
                {
                    public void actionPerformed(ActionEvent event)
                    {
                        quit();
                    }
                });


        isSessionOpened = false;

        dispatcher = new DEViseCmdDispatcher(this);

        if (sessionName != null) {
            int index = sessionName.lastIndexOf('/');
            if (index > 0) {
                currentDir = currentDir + "/" + sessionName.substring(0, index);
                currentSession = sessionName.substring(index + 1, sessionName.length());
            } else {
                currentSession = sessionName;
            }

            dispatcher.start("JAVAC_SetDisplaySize " + DEViseGlobals.screenSize.width + " " + DEViseGlobals.screenSize.height + "\n" + "JAVAC_OpenSession {" + currentDir + "/" + currentSession + "}");
        }
    }

    // print out message to debug window
    public void pn(String msg, int level)
    {
        if (debugLevel > 0) {
            debugWindow.pn(msg, level);
        }
    }

    public void pn(String msg)
    {
        pn(msg, 1);
    }

    public void p(String msg, int level)
    {
        if (debugLevel > 0) {
            debugWindow.p(msg, level);
        }
    }

    public void p(String msg)
    {
        p(msg, 1);
    }

    // show message in message box
    public String showMsg(String msg, String title, int style)
    {
        if (msgbox == null) {
            msgbox = new YMsgBox(parentFrame, isCenterScreen, true, msg, title, style, DEViseGlobals.font, DEViseGlobals.bg, DEViseGlobals.fg);
            msgbox.open();
            String result = msgbox.getResult();
            msgbox = null;
            return result;
        } else {
            YMsgBox box = new YMsgBox(parentFrame, isCenterScreen, true, msg, title, style, DEViseGlobals.font, DEViseGlobals.bg, DEViseGlobals.fg);
            box.open();
            String result = box.getResult();
            box = null;
            return result;
        }
    }

    public String showMsg(String msg)
    {
        return showMsg(msg, null, YMsgBox.YMBXOK);
    }

    public String confirmMsg(String msg)
    {
        return showMsg(msg, "Confirm", YMsgBox.YMBXYESNO);
    }

    public void showSession(String[] msg, boolean flag)
    {
        if (flag) {
            if (sessiondlg != null) {
                sessiondlg.setSessionList(msg);
            } else {
                sessiondlg = new SessionDlg(this, parentFrame, isCenterScreen, msg);
                sessiondlg.open();
            }
        } else {
            showMsg(msg[0]);
        }
    }

    public void showRecord(String[] msg)
    {
        recorddlg = new RecordDlg(parentFrame, isCenterScreen, msg);
        recorddlg.open();
        recorddlg = null;
    }

    public void showServerState(String msg)
    {
        statedlg = new ServerStateDlg(parentFrame, isCenterScreen, msg);
        statedlg.open();
        statedlg = null;
    }

    public void showSetting()
    {
        settingdlg = new SettingDlg(this, parentFrame, isCenterScreen);
        settingdlg.open();
        settingdlg = null;
    }

    public boolean isShowingMsg()
    {
        if (sessiondlg != null || settingdlg != null || statedlg != null || recorddlg != null || msgbox != null) {
            return true;
        } else {
            return false;
        }
    }

    public synchronized boolean getQuitStatus()
    {
        return isQuit;
    }

    public synchronized void quit()
    {
        if (isQuit)
            return;

        if (dispatcher != null) {
            dispatcher.stop(true, true);
        }

        isQuit = true;
        dispatcher = null;

        if (!DEViseGlobals.inBrowser) {
            if (DEViseGlobals.isApplet)
                parentFrame.dispose();
            else
                System.exit(0);
        }
    }
}


class RecordDlg extends Dialog
{
    String[] attrs = null;
    Button okButton = new Button("  OK  ");
    private boolean status = false;

    public RecordDlg(Frame owner, boolean isCenterScreen, String[] data)
    {
        super(owner, true);

        attrs = data;

        setBackground(DEViseGlobals.bg);
        setForeground(DEViseGlobals.fg);
        setFont(DEViseGlobals.font);

        setTitle("Record Attributes");

        okButton.setBackground(DEViseGlobals.bg);
        okButton.setForeground(DEViseGlobals.fg);
        okButton.setFont(DEViseGlobals.font);

        int size = attrs.length - 1;
        Label[] label = null;
        if (size == 0) {
            label = new Label[1];
            label[0] = new Label("");
        } else {
            label = new Label[size];
            for (int i = 0; i < size; i++) {
                label[i] = new Label(attrs[i + 1]);
            }
        }

        DEViseComponentPanel panel = new DEViseComponentPanel(label, "Vertical", 0);
        for (int i = 0; i < size; i++)
            label[i].setAlignment(Label.LEFT);

        // set layout manager
        GridBagLayout  gridbag = new GridBagLayout();
        GridBagConstraints  c = new GridBagConstraints();
        setLayout(gridbag);
        //c.gridx = GridBagConstraints.RELATIVE;
        //c.gridy = GridBagConstraints.RELATIVE;
        c.gridwidth = GridBagConstraints.REMAINDER;
        //c.gridheight = 1;
        c.fill = GridBagConstraints.NONE;
        c.insets = new Insets(10, 10, 10, 10);
        //c.ipadx = 0;
        //c.ipady = 0;
        c.anchor = GridBagConstraints.CENTER;
        c.weightx = 1.0;
        c.weighty = 1.0;

        gridbag.setConstraints(panel, c);
        add(panel);
        gridbag.setConstraints(okButton, c);
        add(okButton);

        pack();

        Dimension panesize = panel.getPreferredSize();
        if (panesize.width > (DEViseGlobals.maxScreenSize.width - 120) || panesize.height > (DEViseGlobals.maxScreenSize.height - 80)) {
            if (panesize.width > (DEViseGlobals.maxScreenSize.width - 120)) {
                panesize.width = DEViseGlobals.maxScreenSize.width - 120;
            }

            if (panesize.height > (DEViseGlobals.maxScreenSize.height - 80)) {
                panesize.height = DEViseGlobals.maxScreenSize.height - 80;
            }

            ScrollPane pane = new ScrollPane();
            pane.setSize(panesize);
            pane.add(panel);

            removeAll();
            gridbag.setConstraints(pane, c);
            add(pane);
            gridbag.setConstraints(okButton, c);
            add(okButton);

            pack();
        }

        // reposition the window
        Point parentLoc = null;
        Dimension parentSize = null;

        if (isCenterScreen) {
            Toolkit kit = Toolkit.getDefaultToolkit();
            parentSize = kit.getScreenSize();
            parentLoc = new Point(0, 0);
        } else {
            parentLoc = owner.getLocation();
            parentSize = owner.getSize();
        }

        Dimension mysize = getSize();
        parentLoc.y += parentSize.height / 2;
        parentLoc.x += parentSize.width / 2;
        parentLoc.y -= mysize.height / 2;
        parentLoc.x -= mysize.width / 2;
        setLocation(parentLoc);

        this.enableEvents(AWTEvent.WINDOW_EVENT_MASK);

        okButton.addActionListener(new ActionListener()
                {
                    public void actionPerformed(ActionEvent event)
                    {
                        close();
                    }
                });

    }

    protected void processEvent(AWTEvent event)
    {
        if (event.getID() == WindowEvent.WINDOW_CLOSING) {
            close();
            return;
        }

        super.processEvent(event);
    }

    // If this dialog is a modal dialog, the show() or setVisible(true) method
    // will block current thread(i.e. the thread that access this method, may
    // be the event dispatcher thread) until setVisible(false) or dispose() is
    // called
    // In JDK1.1, any thread that access AWT method is acting as a event
    // dispatcher thread
    public void open()
    {
        status = true;
        setVisible(true);
    }

    public synchronized void close()
    {
        if (status) {
            dispose();

            status = false;
        }
    }

    public synchronized boolean getStatus()
    {
        return status;
    }
}


class SessionDlg extends Frame
{
    private jsdevisec jsc = null;

    private String sessionName = null;
    private java.awt.List fileList = null;
    private Label label = new Label("Current available sessions in directory    ");
    private Label directory = new Label("");
    private Button okButton = new Button("OK");
    private Button cancelButton = new Button("Cancel");
    private String[] sessions = null;
    private boolean[] sessionTypes = null;
    private String[] sessionNames = null;

    private boolean status = false;

    public SessionDlg(jsdevisec what, Frame owner, boolean isCenterScreen, String[] data)
    {
        jsc = what;

        setBackground(DEViseGlobals.bg);
        setForeground(DEViseGlobals.fg);
        setFont(DEViseGlobals.font);

        setTitle("JavaScreen Open Dialog");

        label.setFont(new Font("Serif", Font.BOLD, 16));
        //label.setFont(DEViseGlobals.font);
        directory.setText("/" + jsc.currentDir);
        directory.setFont(DEViseGlobals.font);

        fileList = new java.awt.List(8, false);
        fileList.setBackground(DEViseGlobals.textBg);
        //fileList.setBackground(Color.white);
        fileList.setForeground(DEViseGlobals.textFg);
        fileList.setFont(DEViseGlobals.textFont);

        setSessionList(data);

        Button [] button = new Button[2];
        button[0] = okButton;
        button[1] = cancelButton;
        DEViseComponentPanel panel = new DEViseComponentPanel(button, "Horizontal", 20);

        // set layout manager
        GridBagLayout  gridbag = new GridBagLayout();
        GridBagConstraints  c = new GridBagConstraints();
        setLayout(gridbag);
        //c.gridx = GridBagConstraints.RELATIVE;
        //c.gridy = GridBagConstraints.RELATIVE;
        c.gridwidth = GridBagConstraints.REMAINDER;
        //c.gridheight = 1;
        c.fill = GridBagConstraints.BOTH;
        //c.ipadx = 0;
        //c.ipady = 0;
        c.anchor = GridBagConstraints.CENTER;
        c.weightx = 1.0;
        c.weighty = 1.0;

        c.insets = new Insets(5, 10, 0, 10);
        gridbag.setConstraints(label, c);
        add(label);
        c.insets = new Insets(0, 10, 5, 10);
        gridbag.setConstraints(directory, c);
        add(directory);
        c.insets = new Insets(5, 10, 5, 10);
        gridbag.setConstraints(fileList, c);
        add(fileList);
        gridbag.setConstraints(panel, c);
        add(panel);

        pack();

        // reposition the window
        Point parentLoc = null;
        Dimension parentSize = null;

        if (isCenterScreen) {
            Toolkit kit = Toolkit.getDefaultToolkit();
            parentSize = kit.getScreenSize();
            parentLoc = new Point(0, 0);
        } else {
            parentLoc = owner.getLocation();
            parentSize = owner.getSize();
        }

        Dimension mysize = getSize();
        parentLoc.y += parentSize.height / 2;
        parentLoc.x += parentSize.width / 2;
        parentLoc.y -= mysize.height / 2;
        parentLoc.x -= mysize.width / 2;
        setLocation(parentLoc);

        this.enableEvents(AWTEvent.WINDOW_EVENT_MASK);

        fileList.addMouseListener(new MouseAdapter()
                {
                    public void mouseClicked(MouseEvent event)
                    {
                        if (event.getClickCount() > 1) {
                            if (fileList.getItemCount() > 0) {
                                int idx = fileList.getSelectedIndex();
                                if (idx != -1) {
                                    sessionName = fileList.getItem(idx);
                                    if (sessionName.startsWith("[")) {
                                        String[] name = DEViseGlobals.parseString(sessionName, '[', ']');
                                        if (name[0].equals("..")) {
                                            if (jsc.currentDir.equals(jsc.rootDir)) {
                                                jsc.showMsg("You do not have access to this directory!");
                                                return;
                                            }

                                            int index = jsc.currentDir.lastIndexOf('/');
                                            if (index > 0) {
                                                jsc.currentDir = jsc.currentDir.substring(0, index);
                                            } else {
                                                jsc.showMsg("Invalid current directory \"" + jsc.currentDir + "\"!");
                                                jsc.currentDir = jsc.rootDir;
                                                close();
                                            }
                                        } else {
                                            jsc.currentDir = jsc.currentDir + "/" + name[0];
                                        }

                                        directory.setText("/" + jsc.currentDir);
                                        validate();

                                        //String dir = (jsc.currentDir).substring(14);

                                        jsc.dispatcher.start("JAVAC_GetSessionList {" + jsc.currentDir + "}");
                                    } else {
                                        jsc.currentSession = sessionName;
                                        jsc.dispatcher.start("JAVAC_SetDisplaySize " + DEViseGlobals.screenSize.width + " " + DEViseGlobals.screenSize.height
                                                                 + "\nJAVAC_OpenSession {" + jsc.currentDir + "/" + sessionName + "}");
                                        close();
                                    }
                                }
                            }
                        }
                    }
                });

        okButton.addActionListener(new ActionListener()
                {
                    public void actionPerformed(ActionEvent event)
                    {
                        if (fileList.getItemCount() > 0) {
                            int idx = fileList.getSelectedIndex();
                            if (idx != -1) {
                                sessionName = fileList.getItem(idx);
                                if (sessionName.startsWith("[")) {
                                    String[] name = DEViseGlobals.parseString(sessionName, '[', ']');
                                    if (name[0].equals("..")) {
                                        if (jsc.currentDir.equals(jsc.rootDir)) {
                                            jsc.showMsg("You do not have access to this directory!");
                                            return;
                                        }

                                        int index = jsc.currentDir.lastIndexOf('/');
                                        if (index > 0) {
                                            jsc.currentDir = jsc.currentDir.substring(0, index);
                                        } else {
                                            jsc.showMsg("Invalid current directory \"" + jsc.currentDir + "\"!");
                                            jsc.currentDir = jsc.rootDir;
                                            close();
                                        }
                                    } else {
                                        jsc.currentDir = jsc.currentDir + "/" + name[0];
                                    }

                                    directory.setText("/" + jsc.currentDir);
                                    validate();

                                    jsc.dispatcher.start("JAVAC_GetSessionList {" + jsc.currentDir + "}");
                                } else {
                                    jsc.currentSession = sessionName;
                                    jsc.dispatcher.start("JAVAC_SetDisplaySize " + DEViseGlobals.screenSize.width + " " + DEViseGlobals.screenSize.height
                                                             + "\nJAVAC_OpenSession {" + jsc.currentDir + "/" + sessionName + "}");
                                    close();
                                }
                            }
                        }
                    }
                });

        cancelButton.addActionListener(new ActionListener()
                {
                    public void actionPerformed(ActionEvent event)
                    {
                        close();
                    }
                });

    }

    public void setSessionList(String[] data)
    {
        if (data == null) {
            data = new String[4];
            data[0] = new String("");
            data[1] = new String(" ");
            data[2] = new String("0");
            data[3] = new String("0");
        }

        sessions = data;

        // need to correct for num < 1
        int number = (sessions.length - 1) / 3;
        sessionNames = new String[number];
        sessionTypes = new boolean[number];
        String tmpstr = null;
        for (int i = 0; i < number; i++) {
            sessionNames[i] = sessions[i * 3 + 1];
            tmpstr = sessions[i * 3 + 2];
            if (tmpstr.equals("0")) {
                sessionTypes[i] = true;
            } else {
                sessionTypes[i] = false;
            }
        }

        fileList.removeAll();

        for (int i = 0; i < number; i++) {
            if (sessionTypes[i]) {
                fileList.add(sessionNames[i]);
            } else {
                fileList.add("[" + sessionNames[i] + "]");
            }
        }

        validate();
    }

    protected void processEvent(AWTEvent event)
    {
        if (event.getID() == WindowEvent.WINDOW_CLOSING) {
            close();
            return;
        }

        super.processEvent(event);
    }

    // If this dialog is a modal dialog, the show() or setVisible(true) method
    // will block current thread(i.e. the thread that access this method, may
    // be the event dispatcher thread) until setVisible(false) or dispose() is
    // called
    // In JDK1.1, any thread that access AWT method is acting as a event
    // dispatcher thread
    public void open()
    {
        status = true;
        setVisible(true);
    }

    public synchronized void close()
    {
        if (status) {
            dispose();

            status = false;

            jsc.sessiondlg = null;
        }
    }

    public synchronized boolean getStatus()
    {
        return status;
    }
}


class SettingDlg extends Dialog
{
    jsdevisec jsc = null;
    public TextField screenX = new TextField(4);
    public TextField screenY = new TextField(4);
    public Button setButton = new Button("   Set   ");
    public Button statButton = new Button("Request");
    private boolean status = false;

    public SettingDlg(jsdevisec what, Frame owner, boolean isCenterScreen)
    {
        super(owner, true);

        jsc = what;

        setBackground(DEViseGlobals.bg);
        setForeground(DEViseGlobals.fg);
        setFont(DEViseGlobals.font);

        setTitle("JavaScreen Setting");

        setButton.setBackground(DEViseGlobals.bg);
        setButton.setForeground(DEViseGlobals.fg);
        setButton.setFont(DEViseGlobals.font);

        screenX.setBackground(DEViseGlobals.textBg);
        screenX.setForeground(DEViseGlobals.textFg);
        screenX.setFont(DEViseGlobals.textFont);

        screenY.setBackground(DEViseGlobals.textBg);
        screenY.setForeground(DEViseGlobals.textFg);
        screenY.setFont(DEViseGlobals.textFont);

        screenX.setText("" + DEViseGlobals.screenSize.width);
        screenY.setText("" + DEViseGlobals.screenSize.height);

        statButton.setBackground(DEViseGlobals.bg);
        statButton.setForeground(DEViseGlobals.fg);
        statButton.setFont(DEViseGlobals.font);

        if (DEViseGlobals.inBrowser) {
            screenX.setEditable(false);
            screenY.setEditable(false);
            setButton.setEnabled(false);
        }

        // set layout manager
        GridBagLayout  gridbag = new GridBagLayout();
        GridBagConstraints  c = new GridBagConstraints();
        setLayout(gridbag);

        //c.gridx = GridBagConstraints.RELATIVE;
        //c.gridy = GridBagConstraints.RELATIVE;
        c.gridwidth = GridBagConstraints.REMAINDER;
        //c.gridheight = 1;
        c.fill = GridBagConstraints.BOTH;
        //c.ipadx = 0;
        //c.ipady = 0;
        c.anchor = GridBagConstraints.CENTER;
        c.weightx = 1.0;
        c.weighty = 1.0;

        c.insets = new Insets(10, 10, 0, 0);
        c.gridwidth = 1;
        Label label1 = new Label("JavaScreen Size:");
        gridbag.setConstraints(label1, c);
        add(label1);

        c.insets = new Insets(10, 0, 0, 5);
        gridbag.setConstraints(screenX, c);
        add(screenX);

        gridbag.setConstraints(screenY, c);
        add(screenY);

        c.insets = new Insets(10, 10, 0, 10);
        c.gridwidth = GridBagConstraints.REMAINDER;
        gridbag.setConstraints(setButton, c);
        add(setButton);

        c.insets = new Insets(10, 10, 10, 0);
        c.gridwidth = 1;
        Label label2 = new Label("JSPOP Status:");
        gridbag.setConstraints(label2, c);
        add(label2);

        c.insets = new Insets(10, 0, 10, 10);
        c.gridwidth = GridBagConstraints.REMAINDER;
        gridbag.setConstraints(statButton, c);
        add(statButton);

        pack();

        // reposition the window
        Point parentLoc = null;
        Dimension parentSize = null;

        if (isCenterScreen) {
            Toolkit kit = Toolkit.getDefaultToolkit();
            parentSize = kit.getScreenSize();
            parentLoc = new Point(0, 0);
        } else {
            parentLoc = owner.getLocation();
            parentSize = owner.getSize();
        }

        Dimension mysize = getSize();
        parentLoc.y += parentSize.height / 2;
        parentLoc.x += parentSize.width / 2;
        parentLoc.y -= mysize.height / 2;
        parentLoc.x -= mysize.width / 2;
        setLocation(parentLoc);

        this.enableEvents(AWTEvent.WINDOW_EVENT_MASK);

        setButton.addActionListener(new ActionListener()
                {
                    public void actionPerformed(ActionEvent event)
                    {
                        if (jsc.isSessionOpened) {
                            jsc.showMsg("You already have a session opened!\nPlease close current session first!");
                            return;
                        }

                        int x = 0, y = 0;

                        try {
                            x = Integer.parseInt(screenX.getText());
                            y = Integer.parseInt(screenY.getText());

                            if (x < DEViseGlobals.minScreenSize.width || x > DEViseGlobals.maxScreenSize.width
                                || y < DEViseGlobals.minScreenSize.height || y > DEViseGlobals.maxScreenSize.height) {
                                throw new NumberFormatException();
                            } else {
                                jsc.jscreen.setScreenDim(x, y);
                                close();
                            }
                        } catch (NumberFormatException e) {
                            jsc.showMsg("Invalid screen size specified!\nJavaScreen size must be larger than ("
                                         + DEViseGlobals.minScreenSize.width + ", " + DEViseGlobals.minScreenSize.height
                                         + ") and smaller than ("
                                         + DEViseGlobals.maxScreenSize.width + ", " + DEViseGlobals.maxScreenSize.height + ")");
                        }
                    }
                });

        statButton.addActionListener(new ActionListener()
                {
                    public void actionPerformed(ActionEvent event)
                    {
                        jsc.dispatcher.start("JAVAC_GetServerState");

                        close();
                    }
                });
    }

    protected void processEvent(AWTEvent event)
    {
        if (event.getID() == WindowEvent.WINDOW_CLOSING) {
            close();
            return;
        }

        super.processEvent(event);
    }

    // If this dialog is a modal dialog, the show() or setVisible(true) method
    // will block current thread(i.e. the thread that access this method, may
    // be the event dispatcher thread) until setVisible(false) or dispose() is
    // called
    // In JDK1.1, any thread that access AWT method is acting as a event
    // dispatcher thread
    public void open()
    {
        status = true;
        setVisible(true);
    }

    public synchronized void close()
    {
        if (status) {
            dispose();

            status = false;
        }
    }

    public synchronized boolean getStatus()
    {
        return status;
    }
}


class ServerStateDlg extends Dialog
{
    private java.awt.List serverList = null, activeClientList = null, suspendClientList = null;
    private Label label1 = new Label("Current active server:");
    private Label label2 = new Label("Current active client:");
    private Label label3 = new Label("Current suspended client:");
    private Button okButton = new Button("   OK   ");

    private boolean status = false;

    public ServerStateDlg(Frame owner, boolean isCenterScreen, String data)
    {
        super(owner, true);

        String[] list = DEViseGlobals.parseStr(data, " ");
        String[] list1 = null, list2 = null, list3 = null;

        if (list != null && list.length > 3) {
            try {
                int number1 = Integer.parseInt(list[0]);
                if (number1 != 0) {
                    list1 = new String[number1];
                    for (int i = 0; i < number1; i++) {
                        list1[i] = list[i + 1];
                    }
                }

                int number2 = Integer.parseInt(list[number1 + 1]);
                if (number2 != 0) {
                    list2 = new String[number2];
                    for (int i = 0; i < number2; i++) {
                        list2[i] = list[i + 2 + number1];
                    }
                }

                int number3 = Integer.parseInt(list[number1 + number2 + 2]);
                if (number3 != 0) {
                    list3 = new String[number3];
                    for (int i = 0; i < number3; i++) {
                        list3[i] = list[i + 3 + number1 + number2];
                    }
                }
            } catch (NumberFormatException e) {
            }
        }

        setBackground(DEViseGlobals.bg);
        setForeground(DEViseGlobals.fg);
        setFont(DEViseGlobals.font);

        setTitle("JSPOP current state");

        label1.setFont(new Font("Serif", Font.BOLD, 16));
        label2.setFont(new Font("Serif", Font.BOLD, 16));
        label3.setFont(new Font("Serif", Font.BOLD, 16));

        serverList = new java.awt.List(4, false);
        serverList.setBackground(DEViseGlobals.textBg);
        serverList.setForeground(DEViseGlobals.textFg);
        serverList.setFont(DEViseGlobals.textFont);
        if (list1 != null) {
            for (int i = 0; i < list1.length; i++) {
                serverList.add(list1[i]);
            }
        }
        activeClientList = new java.awt.List(6, false);
        activeClientList.setBackground(DEViseGlobals.textBg);
        activeClientList.setForeground(DEViseGlobals.textFg);
        activeClientList.setFont(DEViseGlobals.textFont);
        if (list2 != null) {
            for (int i = 0; i < list2.length; i++) {
                activeClientList.add(list2[i]);
            }
        }
        suspendClientList = new java.awt.List(6, false);
        suspendClientList.setBackground(DEViseGlobals.textBg);
        suspendClientList.setForeground(DEViseGlobals.textFg);
        suspendClientList.setFont(DEViseGlobals.textFont);
        if (list3 != null) {
            for (int i = 0; i < list3.length; i++) {
                suspendClientList.add(list3[i]);
            }
        }

        okButton.setBackground(DEViseGlobals.bg);
        okButton.setForeground(DEViseGlobals.fg);
        okButton.setFont(DEViseGlobals.font);

        // set layout manager
        GridBagLayout  gridbag = new GridBagLayout();
        GridBagConstraints  c = new GridBagConstraints();
        setLayout(gridbag);
        //c.gridx = GridBagConstraints.RELATIVE;
        //c.gridy = GridBagConstraints.RELATIVE;
        c.gridwidth = GridBagConstraints.REMAINDER;
        //c.gridheight = 1;
        c.fill = GridBagConstraints.BOTH;
        c.insets = new Insets(5, 10, 5, 10);
        //c.ipadx = 0;
        //c.ipady = 0;
        c.anchor = GridBagConstraints.CENTER;
        c.weightx = 1.0;
        c.weighty = 1.0;

        gridbag.setConstraints(label1, c);
        add(label1);
        gridbag.setConstraints(serverList, c);
        add(serverList);
        gridbag.setConstraints(label2, c);
        add(label2);
        gridbag.setConstraints(activeClientList, c);
        add(activeClientList);
        gridbag.setConstraints(label3, c);
        add(label3);
        gridbag.setConstraints(suspendClientList, c);
        add(suspendClientList);

        gridbag.setConstraints(okButton, c);
        add(okButton);

        pack();

        // reposition the window
        Point parentLoc = null;
        Dimension parentSize = null;

        if (isCenterScreen) {
            Toolkit kit = Toolkit.getDefaultToolkit();
            parentSize = kit.getScreenSize();
            parentLoc = new Point(0, 0);
        } else {
            parentLoc = owner.getLocation();
            parentSize = owner.getSize();
        }

        Dimension mysize = getSize();
        parentLoc.y += parentSize.height / 2;
        parentLoc.x += parentSize.width / 2;
        parentLoc.y -= mysize.height / 2;
        parentLoc.x -= mysize.width / 2;
        setLocation(parentLoc);

        this.enableEvents(AWTEvent.WINDOW_EVENT_MASK);

        okButton.addActionListener(new ActionListener()
                {
                    public void actionPerformed(ActionEvent event)
                    {
                        close();
                    }
                });

    }

    protected void processEvent(AWTEvent event)
    {
        if (event.getID() == WindowEvent.WINDOW_CLOSING) {
            close();
            return;
        }

        super.processEvent(event);
    }

    // If this dialog is a modal dialog, the show() or setVisible(true) method
    // will block current thread(i.e. the thread that access this method, may
    // be the event dispatcher thread) until setVisible(false) or dispose() is
    // called
    // In JDK1.1, any thread that access AWT method is acting as a event
    // dispatcher thread
    public void open()
    {
        status = true;
        setVisible(true);
    }

    public synchronized void close()
    {
        if (status) {
            dispose();

            status = false;
        }
    }

    public synchronized boolean getStatus()
    {
        return status;
    }
}
