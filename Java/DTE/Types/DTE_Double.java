package Types;

import java.io.*;
import java.lang.*;

public class DTE_Double extends DTE_Type  //implements Cloneable 
{
  double val;

  public String toString()
  {
     return String.valueOf( val );
  }

  public DTE_Double()
  {
    val = 0;
  }

  public DTE_Double(double i)
  {
    val = i;
  }
  
  public TypeDesc getType( )
  {
    return new DoubleDesc( );
  }

  public double getValue( )
  {
    return val;
  }

  public void setValue( double d)
  {
    val = d;
  }

  public boolean read(StreamTokenizer st) throws IOException 
  {
    int status = st.nextToken();
    if(status == StreamTokenizer.TT_EOF)
      return false;
    
    if(status != StreamTokenizer.TT_NUMBER)
      {
	int lineno = st.lineno();
	System.err.println("The data on line " + lineno + " is not a double!");
	return false;
      }
    
    val = st.nval;
    return true;
  }
 
  public void print(PrintWriter ps)
  {
    ps.print(val);
    ps.print(" ");
  }

  public void print(PrintStream ps)
  {
    ps.print(val);
    ps.print(" "); 
  }

    /*
  public Object clone()
  {
    return new DTE_Double(val);
  }
    */

    public void copyTo(DTE_Type d)
	{
	    ((DTE_Double)d).val = val;
	}
}


