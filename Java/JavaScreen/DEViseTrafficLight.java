import java.awt.*;
import java.awt.event.*;

public class DEViseTrafficLight extends Panel
{
    Image onImage = null, offImage = null;
    YImageCanvas [] canvas = new YImageCanvas[4];
    //Label [] label = new Label[4];
    YImageCanvas [] label = new YImageCanvas[3];
    String[] c = {"S", "R", "P"};
    String string = null;

    public DEViseTrafficLight(Image offi, Image oni, String s) throws YException
    {
        this(offi, oni, s, null);
    }

    public DEViseTrafficLight(Image offi, Image oni, String s, String align) throws YException
    {
        onImage = oni;
        offImage = offi;

        for (int i = 0; i < 3; i++) {
            canvas[i] = new YImageCanvas(onImage);
            if (!canvas[i].setImage(offImage))
                throw new YException("Invalid Image!");
            //label[i] = new Label(c[i]);
            label[i] = new YImageCanvas(c[i], null, DEViseGlobals.uibgcolor, DEViseGlobals.uifgcolor, 12, 12, 1, 1);
        }
        string = s;
        canvas[3] = new YImageCanvas(string);
        if (align == null) {
            align = "RIGHT";
        }

        setFont(new Font("Monospaced", Font.BOLD, 14));
        setBackground(DEViseGlobals.uibgcolor);
        setForeground(DEViseGlobals.uifgcolor);

        Panel panel = new Panel();
        panel.setLayout(new GridLayout(2, 4));
        panel.setFont(new Font("Monospaced", Font.BOLD, 14));
        panel.setBackground(DEViseGlobals.uibgcolor);
        panel.setForeground(DEViseGlobals.uifgcolor);
        for (int i = 0; i < 3; i++)
            panel.add(label[i]);
        for (int i = 0; i < 3; i++)
            panel.add(canvas[i]);

        if (align == "TOP" || align == "BOTTOM") {
            // set new gridbag layout
            GridBagLayout gridbag = new GridBagLayout();
            GridBagConstraints c = new GridBagConstraints();
            //c.gridx = GridBagConstraints.RELATIVE;
            //c.gridy = GridBagConstraints.RELATIVE;
            c.gridwidth = GridBagConstraints.REMAINDER;
            c.gridheight = 1;
            c.fill = GridBagConstraints.NONE;
            c.insets = new Insets(0, 0, 0, 0);
            c.ipadx = 0;
            c.ipady = 0;
            c.anchor = GridBagConstraints.CENTER;
            //c.weightx = 1.0;
            //c.weighty = 1.0;

            setLayout(gridbag);

            if (align == "TOP") {
                gridbag.setConstraints(canvas[3], c);
                add(canvas[3]);
                gridbag.setConstraints(panel, c);
                add(panel);
            } else {
                gridbag.setConstraints(panel, c);
                add(panel);
                gridbag.setConstraints(canvas[3], c);
                add(canvas[3]);
            }
        } else if (align == "LEFT") {
            add(canvas[3]);
            add(panel);
        } else {
            add(panel);
            add(canvas[3]);
        }
    }

    public void updateImage(int type, int isOn)
    {
        if (type < 0 || type > 3)
            return;

        if (type == 0) {
            for (int i = 0; i < 3; i++) {
                canvas[i].setImage(offImage);
            }
        } else {
            if (isOn == 1) {
                canvas[type - 1].setImage(onImage);
            } else {
                canvas[type - 1].setImage(offImage);
            }
        }
    }

    public void updateCount(String s)
    {
        string = s;
        canvas[3].setString(string);
    }
}
