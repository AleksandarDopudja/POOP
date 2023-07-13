package og;

import java.util.Vector;

public class Team {

	private String uniqueMark;
	Vector<String> members = new Vector<String>();
	
	public Team(String s) {
		uniqueMark=s;
		String um = uniqueMark;
		um = um.substring(1, um.length()-1);
		String[] arrOfStr = um.split("'", -2);
		for (int i = 1, j = 0 ; i<arrOfStr.length; i+=2, j++)
			members.add(arrOfStr[i]);
	}
	
	public int numerOfAthletes() {
		//String um = uniqueMark;
	    //um = um.substring(1, um.length()-1);
		//String[] arrOfStr = um.split("'", -2);
		//int number = 0;        		
		//for (int i = 1 ; i<arrOfStr.length; i+=2) {
			 //number++;
		//}
		//return number;
		return members.size();
	}
	
	public static int numOfAtl(String uniqueMark) {
		String um = uniqueMark;
	    um = um.substring(1, um.length()-1);
		String[] arrOfStr = um.split("'", -2);
		int number = 0;        		
		for (int i = 1 ; i<arrOfStr.length; i+=2) {
			 number++;
		}
		return number;
	}
	
	public Vector<String> getMembers(){
		return members;
	}
	
	
}
