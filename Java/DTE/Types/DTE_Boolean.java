package Types;

import java.io.*;

public class DTE_Boolean extends DTE_Type 
{
  boolean val;
  
  public DTE_Boolean( )
  {
    val = true;
  }
  
     public boolean equals(Object obj){
          if(! getClass().equals(obj.getClass())){
               return false;
          }
          DTE_Boolean cObj = (DTE_Boolean) obj;
          return val == cObj.val;
     }

 /** Create an DTE_Boolean object with value to be b.*/  
  public DTE_Boolean( boolean b )
  {
    val = b;
  }
  
  public String toString( ){
      return String.valueOf( val );
  }

  public TypeDesc getType( )
  {
    return new BooleanDesc( );
  }

  public boolean getValue( )
  {
    return val;
  }

  public void setValue( boolean b )
  {
    val = b;
  }

  /** Read a boolean from the StreamTokenizer s. */
  public boolean read(StreamTokenizer st) throws IOException 
  {
    int status = st.nextToken( );
    if(status == StreamTokenizer.TT_EOF)
      return false;
    
    if(status == StreamTokenizer.TT_NUMBER)
      {
	int lineno = st.lineno( );
	System.err.println("The data on line " + lineno + " is not a Boolean!");
	return false;
      }
    
    // Need to check that this is really an boolean.
    // return 0 if this is not an int and print the msg to stderr.
    // use st.lineno()
    
    val = Boolean.getBoolean(st.sval);
    return true;
  }
  
/** Print to a PrintWriter object "ps".*/
  public void print(PrintWriter ps)
  {
    ps.print(val);
    ps.print(" "); 
  }

/** Print to a PrintStream object "ps".*/
  public void print(PrintStream ps)
  {
    ps.print(val);   
    ps.print(" "); 
  }

  /** Copy this DTE_Boolean object to another DTE_Type object 'd'.*/    
    public void copyTo(DTE_Type d)
	{
	    ((DTE_Boolean)d).val = val;
	}
}

