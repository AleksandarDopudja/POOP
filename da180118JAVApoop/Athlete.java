package og;

import java.util.regex.Matcher;
import java.util.regex.Pattern;

public class Athlete {
	private int uniqueMark;
	private String name;
	private char gender;
	private String years;
 	private String height;
	private String weight;
	
	Athlete(String s) {
		
		Matcher m = Pattern.compile("([0-9]+)!([^!]+)!(.)!([^!]+)!([^!]+)!(.+)").matcher(s);
		
		if(m.find()) { 
			uniqueMark = Integer.parseInt(m.group(1));
			name = m.group(2);
			gender = m.group(3).charAt(0);
			years = m.group(4);
			height = m.group(5);		
			weight = m.group(6);
		}
	}
		
	public int getUniqueMark() {
		return uniqueMark;
	}
	
	public double getHeight() {
		if(height.equals("NA"))return 0;
		return Double.parseDouble(height);
	}
	
	public double getWeight() {
		if(weight.equals("NA"))return 0;
		return Double.parseDouble(weight);
	}
	
	public String toString(){//overriding the toString() method  
		return uniqueMark+":"+name+":"+gender+":"+years+":"+height+":"+weight;
	} 
}
