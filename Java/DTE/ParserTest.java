import java.io.*;
import Iterators.*;
import Types.*;
import Expressions.*;
import Parser.*;


/** This is a main DTE class */

public class ParserTest {
	private Query query;

	void parse(){	// throws parse error

		// Jin has to implement this function and stuff closely related
		// to it.
		// To demonstrate that this function works, run it on bunch of
		// legal queries. It should print back the same query (up to
		// some formatting differences).

		SQLParser parser = new SQLParser(System.in);
		query = parser.query();
		System.out.println("Query was: " + query);
	}

	public static void main(String[] args) throws IOException {
		parse();	
	}
}
