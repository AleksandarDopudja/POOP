package og;

import java.util.regex.Matcher;
import java.util.regex.Pattern;

public class Event {

	private int year;
	private String typeOG;
	private String city;
	private String sport;
	private String discipline;
	private String typeEvent;
	private String country;
	private String uniqueMark;
	private String typeMedal;
	
	Event(int yr,String tyOG,String cty, String sp, String dis, String typEv, String cnt, String unMar, String typMdl){
		year = yr;
		typeOG = tyOG;
		city = cty;
		sport = sp;
		discipline = dis;
		typeEvent = typEv;
		country = cnt;
		uniqueMark = unMar;
		typeMedal = typMdl;
	}
	
	Event(String s) {
		
		Matcher m = Pattern.compile("((\\d+) ([a-zA-z]+))!([^!]+)!([^!]+)!([^!]+)!([^!]+)!([^!]+)!([^!]+)!([a-zA-z]*)").matcher(s);
		
		if(m.find()) { //while
			year =  Integer.parseInt(m.group(2));
			typeOG = m.group(3);
			city = m.group(4);
			sport = m.group(5);
			discipline = m.group(6);
			typeEvent = m.group(7);
			country = m.group(8);
			uniqueMark = m.group(9);
			typeMedal = m.group(10);
		}
	}
	
	public String getUniqueMark() {
		return uniqueMark;
	}
	
	public String getTypeEvent() {
		return typeEvent;
	}
	
	public String getSport() {
		return sport;
	}
	
	public String getTypeMedal() {
		return typeMedal;
	}
	
	public int getYear() {
		return year;
	}
	
	public String getCountry() {
		return country;
	}
	
	public String getDiscipline() {
		return discipline;
	}
	
	public String getTypeOG() {
		return typeOG;
	}
	
	public String toString(){//overriding the toString() method  
		  return year+" "+typeOG+":"+city+":"+sport+":"+discipline+":"+typeEvent+":"+country+":"+uniqueMark+":"+typeMedal;  
	}  

}
