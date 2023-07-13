package og;

import java.awt.List;
import java.util.Collections;
import java.util.Comparator;
import java.util.HashMap;
import java.util.HashSet;
import java.util.Iterator;
import java.util.LinkedHashMap;
import java.util.LinkedList;
import java.util.Map;
import java.util.Set;
import java.util.Vector;
import java.util.stream.Collectors;

import javax.swing.JTextArea;

import java.util.Map.Entry;
import java.util.TreeMap;

public class Filter {

	private Vector<Integer> filterevents = new Vector<Integer>();
	private Vector<Event> events;
	private Map<String,Integer> countCountry = new TreeMap<String,Integer>();
	
	private Vector<Integer> summerEvents = new Vector<Integer>();
	private Vector<Integer> winterEvents = new Vector<Integer>();
	
	public Filter(Vector<Event> ptr) {
		events = ptr;
	}
	
	public void setFilter(String sport, int year, String typeEvent, String medalType, String typeOG) {		
		Iterator<Event> it = events.iterator();
		Event i;
		int j=0;
	    while(it.hasNext()) {
	      i = it.next();
	      if((sport.equals("") || i.getSport().equals(sport)) && (year==0 || i.getYear()==year) && (typeEvent.equals("") || i.getTypeEvent().equals(typeEvent)) && (medalType.equals("") || i.getTypeMedal().equals(medalType)) && (typeOG.equals("") || i.getTypeOG().equals(typeOG))) {
	    	  
	    	  filterevents.add(j);
	    	  
	    	  if(i.getTypeOG().equals("Summer"))summerEvents.add(j);
	    	  else
	    		  winterEvents.add(j);
	    	  
	    	  if(countCountry.containsKey(i.getCountry())) {
	    		  if(i.getTypeEvent().equals("Individual"))countCountry.put(i.getCountry(), countCountry.get(i.getCountry())+1);
	    		  else
	    			  countCountry.put(i.getCountry(), countCountry.get(i.getCountry())+Team.numOfAtl(i.getUniqueMark()));
	    	  }
	    	  else {
	    		  if(i.getTypeEvent().equals("Individual"))countCountry.put(i.getCountry(), 1);
	    		  else
	    			  countCountry.put(i.getCountry(), Team.numOfAtl(i.getUniqueMark()));
	    	  }
	    	  //System.out.println(i);
	      }
	      j++;
	      //System.out.println(i);
	    }
	    
	    //Collections.sort(filterevents);
	    
	    countCountry = countCountry.entrySet()
	    		.stream()
	    		.sorted(Map.Entry.<String, Integer>comparingByValue().reversed())
	    		.collect(Collectors.toMap(Map.Entry::getKey,
	    		               Map.Entry::getValue, (e1, e2) -> e1, LinkedHashMap::new));
	    
	}
	
	public void print(JTextArea textArea) {
		//Iterator<Event> it = filterevents.iterator();
		//Event i;
	    //while(it.hasNext()) {
	      //i = it.next();
	      //System.out.println(it.next());
	    //}
		for(int i=0;i<filterevents.size();i++) {
			//System.out.println(events.get(filterevents.get(i)));
			textArea.append(events.get(filterevents.get(i)).toString()+"\n");
		}
	}
	
	void printCountCountry() {
		Iterator<Entry<String, Integer>> itr = countCountry.entrySet().iterator();
		while(itr.hasNext()) {
			
			System.out.println(itr.next());
		}
	}
	
    public Vector<Integer> getFilterEvents(){
    	return filterevents;
    }
    
    public Map<String,Integer> getCountCountry(){
    	return countCountry;
    }
    
    public Set<Integer> getAllYears(){
    	Set<Integer> years = new HashSet<Integer>();		
		for(int i : filterevents) {
			years.add(events.get(i).getYear());
		}
		return years;
    }
    
    public Vector<Integer> getFilterWinterEvents(){
    	return winterEvents;
    }
    
    public Vector<Integer> getFilterSummerEvents(){
    	return summerEvents;
    }
    
    Vector<Event> getEvents(){
    	return events;
    }
}
