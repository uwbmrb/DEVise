import java.io.*;
import java.text.ParseException;

public class LineTokens {
	public int seqNumber;
	public int csi;
	private StreamTokenizer st;


	LineTokens (StreamTokenizer st) {
	    this.st = st;
	}


	public int readAndTokenLine() {
	    try {
		if (st.nextToken() == st.TT_EOF)
		    return st.TT_EOF;
		else if (st.ttype != st.TT_NUMBER)
		    throw new ParseException(
			     "Expected number for sequence code, not string", 0);
		else
		    seqNumber = (int)st.nval;
		
		// compute consensus info here		
		if (st.nextToken() != st.TT_NUMBER)
		    throw new ParseException(
			     "Expected number for ha_deltashift, not string", 0);
		else		    
		    csi = (int)st.nval;
		
		if (st.nextToken() != st.TT_NUMBER)
		    throw new ParseException(
			     "Expected number for c_deltashift, not string", 0);
		else		    
		    csi -= (int)st.nval;

		if (st.nextToken() != st.TT_NUMBER)
		    throw new ParseException(
			     "Expected number for ca_deltashift, not string", 0);
		else		    
		    csi -= (int)st.nval;

		st.nextToken();	// skip cb_deltashift
		
		if (csi < 0)
		    csi = -1;
		else if (csi > 0)
		    csi = 1;
		else
		    csi = 0;
		

	    } catch (ParseException e) {
		System.err.println("Parse Exception: "
				   + e.getMessage() );
		
	    } catch (IOException e) {
		System.err.println("IO Exception: "
				   + e.getMessage() );
	    }
	    
	    return st.ttype;
	}
    }
