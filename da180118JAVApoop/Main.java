package og;

import java.awt.BorderLayout;
import java.awt.Color;
import java.awt.Graphics;
import java.awt.GridLayout;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.WindowEvent;
import java.io.BufferedReader;
import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;
import java.util.HashMap;
import java.util.HashSet;
import java.util.Iterator;
import java.util.Map;
import java.util.Map.Entry;
import java.util.Set;
import java.util.Vector;

import javax.swing.ButtonGroup;
import javax.swing.JButton;
import javax.swing.JCheckBox;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JPanel;
import javax.swing.JRadioButton;
import javax.swing.JScrollPane;
import javax.swing.JTextArea;
import javax.swing.JTextField;
import javax.swing.SwingUtilities;

public class Main {

	private JFrame page;
	private Vector<Event> events = new Vector<Event>();
	private Map<Integer,Athlete> athletes=new HashMap<Integer,Athlete>();  
	private Map<String,Team> teams = new HashMap<String,Team>();
	private Filter f;
	private PieChart pc;
	private JTextArea textArea;
	private JButton load = new JButton("Load");  
	private JButton filter = new JButton("Filter");
	private JButton manipulation = new JButton("Manipulation");
	private JButton graph = new JButton("Graph");
	private JButton pieChart = new JButton("PieChart");
	private JCheckBox singlMode;
	private JTextField t1=new JTextField("");  
	private JTextField year;
	private JTextField eventType;
	private JTextField eventMedal;
	private JTextField sport;
	private JRadioButton numerOfAtl = new JRadioButton("Broj ucesnika", false);  
	private JRadioButton totalNumbOfDis = new JRadioButton("Ukupan broj disciplina", false);
	private JRadioButton avgHeight = new JRadioButton("Prosecna visna", false);
	private JRadioButton avgWeight = new JRadioButton("Prosecna tezina", false);
	private JLabel result = new JLabel("Result");
	private Graph gr;
	private JTextField start = new JTextField("");
	private JTextField end = new JTextField("");
	private String mod="";
	
	Main(){
		page = new JFrame("OG");
		page.setBounds(100,100,800,800);
		page.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		page.setVisible(true);
		page.setLayout(new GridLayout(2,3));
		
		JPanel left = new JPanel();
		left.setLayout(new GridLayout(10,1));
		left.add(load);
		
		JPanel p1 = new JPanel(new GridLayout(1,2));
		JPanel p2 = new JPanel(new BorderLayout());
		p2.add(new JLabel("Godina:"),BorderLayout.WEST);
		p2.add(t1,BorderLayout.CENTER);
		p1.add(p2);
		
		left.add(p1);
		
		left.add(filter);
		
		JPanel options = new JPanel(new GridLayout(2,2));
		
		JLabel l1 = new JLabel("Sport: ");
		sport = new JTextField("");

		JPanel panel1 = new JPanel(new BorderLayout());
		panel1.add(l1,BorderLayout.WEST);
		panel1.add(sport,BorderLayout.CENTER);
		
		options.add(panel1);
		
		JLabel l2 = new JLabel("Godina: ");
		year = new JTextField("");

		JPanel panel2 = new JPanel(new BorderLayout());
		panel2.add(l2,BorderLayout.WEST);
		panel2.add(year,BorderLayout.CENTER);
		
		options.add(panel2);
		
		JLabel l3 = new JLabel("Tip dogadjaja: ");
		eventType = new JTextField("");

		JPanel panel3 = new JPanel(new BorderLayout());
		panel3.add(l3,BorderLayout.WEST);
		panel3.add(eventType,BorderLayout.CENTER);
		
		options.add(panel3);
		
		JLabel l4 = new JLabel("Tip medalje: ");
		eventMedal = new JTextField("");

		JPanel panel4 = new JPanel(new BorderLayout());
		panel4.add(l4,BorderLayout.WEST);
		panel4.add(eventMedal,BorderLayout.CENTER);
		
		options.add(panel4);
		
		left.add(options);
		
		left.add(manipulation);
		
		JPanel panel5 = new JPanel(new GridLayout(2,2)); 
		ButtonGroup group = new ButtonGroup();
		group.add(numerOfAtl);
		group.add(totalNumbOfDis);
		group.add(avgHeight);
		group.add(avgWeight);
		
		panel5.add(numerOfAtl);
		panel5.add(totalNumbOfDis);
		panel5.add(avgHeight);
		panel5.add(avgWeight);
		left.add(panel5);
		
		left.add(result);
		
		left.add(pieChart);
		left.add(graph);
		
		JPanel fromTo = new JPanel(new GridLayout(1,2));
		JPanel pom1 = new JPanel(new BorderLayout());
		pom1.add(new JLabel("Od: "),BorderLayout.WEST);
		pom1.add(start,BorderLayout.CENTER);
		fromTo.add(pom1);
		JPanel pom2 = new JPanel(new BorderLayout());
		pom2.add(new JLabel("Do: "),BorderLayout.WEST);
		pom2.add(end,BorderLayout.CENTER);
		fromTo.add(pom2);
		
		left.add(fromTo);
		
		page.add(left);
		
		showOptions();
		
		//page.add(result);
	}
	
	
	void readEvents(int year) throws FileNotFoundException, IOException {
		File file = new File("C:\\Users\\User\\Desktop\\poop\\events.txt");
		BufferedReader br= new BufferedReader(new FileReader(file));

        String st;
        while ((st = br.readLine()) != null) {
        	Event e = new Event(st);
        	if(year==e.getYear() || year==0)events.add(e);
        	else
        		continue;
        	if(e.getTypeEvent().equals("Individual")) {
        		athletes.putIfAbsent(Integer.parseInt(e.getUniqueMark()), null);
        	}
        	else {
        		String um = e.getUniqueMark();
        		teams.putIfAbsent(um, new Team(um));
        		um = um.substring(1, um.length()-1);
        		String[] arrOfStr = um.split("'", -2);
        		        		
        		 for (int i = 1 ; i<arrOfStr.length; i+=2) {
        			 athletes.putIfAbsent(Integer.parseInt(arrOfStr[i]), null); 
        		 }
        	}
        	//System.out.println(e);
        }
	}
	
	void readAthletes() throws FileNotFoundException, IOException {
		File file = new File("C:\\Users\\User\\Desktop\\poop\\athletes.txt");
		BufferedReader br= new BufferedReader(new FileReader(file));

        String st;
        while ((st = br.readLine()) != null) {
        	Athlete a = new Athlete(st);
        	if(athletes.containsKey(a.getUniqueMark()))athletes.put(a.getUniqueMark(), a);
        	//System.out.println(a);
        }
	}
	
	void printEvents() {
		Iterator<Event> it = events.iterator();
		//Event i;
	    while(it.hasNext()) {
	      //i = it.next();
	      //System.out.println(it.next());
	      textArea.append(it.next().toString()+"\n");
	    }
	}
	
	
	void printAthletes() {
		Iterator<Entry<Integer, Athlete>> itr = athletes.entrySet().iterator();
		while(itr.hasNext()) {
			Athlete a= itr.next().getValue();
			System.out.println(a);
		}
	}
	
	public int numberOfAthletesAllEvents() {
		Vector<Integer> filterevents =  f.getFilterEvents();
		int number=0;
		for(int i : filterevents) {
			if(events.get(i).getTypeEvent().equals("Individual"))number++;
			else
				number+=teams.get(events.get(i).getUniqueMark()).numerOfAthletes();
		}
		
		return number;
	}
	
	public double averageHeightOfAthletes() {
		double sum = 0;
		double n = 0;
		Vector<Integer> filterevents =  f.getFilterEvents();
		for(int i : filterevents) {
			if(events.get(i).getTypeEvent().equals("Individual")) {
				double h = athletes.get(Integer.parseInt(events.get(i).getUniqueMark())).getHeight();
				sum+=h;
				if(h!=0)n++;
			}
			else {
				Team t = teams.get(events.get(i).getUniqueMark());
				Vector<String> mem  = t.getMembers();
				for(int j=0;j<mem.size();j++) {
					double h = athletes.get(Integer.parseInt(mem.get(j))).getHeight();
					sum+=h;
					if(h!=0)n++;
				}
			}
		}
		
		return sum/n;
	}
	
	public double averageWeightOfAthletes() {
		double sum = 0;
		double n = 0;
		Vector<Integer> filterevents =  f.getFilterEvents();
		for(int i : filterevents) {
			if(events.get(i).getTypeEvent().equals("Individual")) {
				double h = athletes.get(Integer.parseInt(events.get(i).getUniqueMark())).getWeight();
				sum+=h;
				if(h!=0)n++;
			}
			else {
				Team t = teams.get(events.get(i).getUniqueMark());
				Vector<String> mem  = t.getMembers();
				for(int j=0;j<mem.size();j++) {
					double h = athletes.get(Integer.parseInt(mem.get(j))).getWeight();
					sum+=h;
					if(h!=0)n++;
				}
			}
		}
		
		return sum/n;
	}
	
	public int totalNumberOfDisciplines() {
		Set<String> disciplines = new HashSet<String>();
		Vector<Integer> filterevents =  f.getFilterEvents();
		for(int i : filterevents) {
			disciplines.add(events.get(i).getDiscipline());
		}
		return disciplines.size();
	}
	
	public void paitPC() {
		pc = new PieChart(f);
		pc.setVisible(true);
		page.add(pc);
		SwingUtilities.updateComponentTreeUI(page);
	}
	
	public void paintGraph() {
		gr= new Graph(f,start.getText().equals("")?1900:Integer.parseInt(start.getText()),end.getText().equals("")?2020:Integer.parseInt(end.getText()), this,mod);
		gr.setVisible(true);
		//JScrollPane scroll = new JScrollPane(gr);
		page.add(gr);
		//page.add(scroll);
		SwingUtilities.updateComponentTreeUI(page);
	}
	
	public void setFilter(String s1,int i,String s2,String s3,String s4) {
		f = new Filter(events);
		f.setFilter(s1,i,s2,s3,s4);
	}
	
	public void showOptions() {

		textArea = new JTextArea(100,100);
		//textArea.setBackground(Color.LIGHT_GRAY);
		JScrollPane scroll = new JScrollPane(textArea);
		textArea.setEditable(false);
		//textArea.setLineWrap(true);
		//textArea.setWrapStyleWord(true);
		
		page.add(scroll);
		
		load.addActionListener(new ActionListener(){  
	    	public void actionPerformed(ActionEvent e){  
	    	             try {
	    	            	result.setText("");
	    	            	events = new Vector<Event>();
						    athletes = new HashMap<Integer,Athlete>();  
							teams = new HashMap<String,Team>();
	    	            	textArea.setText("");
							if(t1.getText().equals(""))readEvents(0);
							else
								readEvents(Integer.parseInt(t1.getText()));
							readAthletes();
							printEvents();
							
							f = new Filter(events);
							f.setFilter("",0,"","","");
							
						} catch (IOException e1) {
							// TODO Auto-generated catch block
							e1.printStackTrace();							
						} 
	    	        }  
	    	    });  
		
		filter.addActionListener(new ActionListener(){  
	    	public void actionPerformed(ActionEvent e){
	    		result.setText("");
	    		textArea.setText("");
	    		int yr = 0;
	    		if(!year.getText().equals("")) yr=Integer.parseInt(year.getText());
	    		f = new Filter(events);
				f.setFilter(sport.getText(), yr, eventType.getText(),eventMedal.getText(),"");
				f.print(textArea); 
	    	}});
		
		manipulation.addActionListener(new ActionListener(){  
	    	public void actionPerformed(ActionEvent e){
	    		result.setText("");
	    		if(numerOfAtl.isSelected()) {
	    			result.setText(numberOfAthletesAllEvents()+"");
	    			//paitPC();
	    		}
	    		else if(totalNumbOfDis.isSelected()) {
	    			result.setText(totalNumberOfDisciplines()+"");
	    			//paintGraph();
	    			//mod="dis";
	    		}
	    		else if(avgHeight.isSelected()) {
	    			result.setText(averageHeightOfAthletes()+"");
	    			//paintGraph();
	    			//mod="hg";
	    		}
	    		else if(avgWeight.isSelected()) {
	    			result.setText(averageWeightOfAthletes()+"");
	    			//paintGraph();
	    			//mod="wg";
	    		}
	    	}});
		
		graph.addActionListener(new ActionListener(){  
	    	public void actionPerformed(ActionEvent e){
	    		
	    		result.setText("");

	    		if(totalNumbOfDis.isSelected()) {
	    			mod="dis";
	    		}
	    		else if(avgHeight.isSelected()) {
	    			mod="hg";
	    		}
	    		else if(avgWeight.isSelected()) {
	    			mod="wg";
	    		}
	    		
	    		paintGraph();
	    	}});
		
		pieChart.addActionListener(new ActionListener(){  
	    	public void actionPerformed(ActionEvent e){
	    		paitPC();
	    	}});
	}
	
	public static void main(String[] args) throws FileNotFoundException, IOException {
		
		Main m = new Main();
		//m.readEvents(0);
		//m.printEvents();
		//m.readAthletes();
		//m.printAthletes();
		
		//f = new Filter(events);
		//f.setFilter("", 0, "", "");
		//f.print();
		//f.printCountCountry();
		//System.out.println(numberOfAthletesAllEvents());
		//System.out.println(totalNumberOfDisciplines());
		//System.out.println(averageHeightOfAthletes());
		//System.out.println(averageWeightOfAthletes());
		//m.paitPC();
		
		
		
	}

}
