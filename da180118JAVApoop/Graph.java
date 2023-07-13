package og;

import java.awt.BasicStroke;
import java.awt.Color;
import java.awt.Dimension;
import java.awt.Font;
import java.awt.FontMetrics;
import java.awt.Graphics;
import java.awt.Graphics2D;
import java.awt.Point;
import java.awt.RenderingHints;
import java.awt.Stroke;
import java.awt.geom.Ellipse2D;
import java.awt.geom.Line2D;
import java.util.ArrayList;
import java.util.Iterator;
import java.util.List;
import java.util.Random;
import java.util.Set;
import java.util.Vector;
import java.util.Map.Entry;

import javax.swing.JFrame;
import javax.swing.JPanel;
import javax.swing.SwingUtilities;

public class Graph extends JPanel {

	private int X = 20,Y = 350;
	private double sliceX = 50;
	private double sliceY = 50;
	private int max_X = 380, max_Y = 300;
	private int min_Height = 50;
	private int min_Year = 1900;
	private int half_I = 1;
	private int value_slice_Y = 50;
	private int value_slice_X = 20;
	private double unit;
	private double unitY;
	private Filter f;
	
	private int min_weight = 50;
	private int max_weight = 100;
	
	private int min_height = 150;
	private int max_height = 220;
	
	private int min_dis = 0;
	private int max_dis = 350;
	
	private int start, end;
	
	private String mod;
	private int nY;
	private int minY;
	
	private Main m;
	
	public Graph(Filter filter, int start, int end , Main m, String mod) {
		this.m=m;
		f = filter;
		this.start = start;
		this.end = end;
		
		//this.start=1900;
		//this.end=2020;
		this.mod=mod;
		
		int rangeY=0;
		if(mod.equals("dis")) {
			nY=7;
			minY=min_dis;
			value_slice_Y=50;
			rangeY=max_dis-min_dis;
		}
		else if(mod.equals("hg")) {
			nY=8;
			minY=min_height;
			value_slice_Y=10;
			rangeY=max_height-min_height;
		}
		else {
			nY=5;
			minY=min_weight;
			value_slice_Y=10;
			rangeY=max_weight-min_weight;
		}
		
		sliceY=(max_Y)/nY;
		
		int numOfYears = this.end - this.start;
		
		int group = 20;
		int n = numOfYears/group;
		//n++;
		if(n==0)n++;
		
		
		sliceX = ((max_X-X-20)/(n));
		//System.out.println(sliceX);
		
		//unit = (double)(max_X-X-20)/numOfYears;
		unit=(double)(sliceX)/value_slice_X;
		unitY = (double)(sliceY)/value_slice_Y;
		//System.out.println(unitY);
	}
	
	public void drawDots(Graphics g) {
		
		Graphics2D g2d = (Graphics2D)g;
		 //g2d.drawOval(X+100,  Y-100, 3, 3);
		
		//Vector<Integer> summer = f.getFilterSummerEvents();
		///System.out.println(summer);
		//Vector<Event> events = f.getEvents();
		
		Set<Integer> years = f.getAllYears();
		
		if(mod.equals("dis")) {
			
			g2d.setColor(Color.RED);
			for(int yr:years) {
				if(yr>=start && yr<=end) {
					m.setFilter("", yr, "", "","Summer");
					int res = m.totalNumberOfDisciplines();
					if(res!=0)g2d.draw(new Ellipse2D.Double(X+20+(yr-start)*unit - 5, Y-(res*unitY), 3, 3));
				}
			}
			
			g2d.setColor(Color.BLUE);
			for(int yr:years) {
				if(yr>=start && yr<=end) {
					m.setFilter("", yr, "", "","Winter");
					int res = m.totalNumberOfDisciplines();
					if(res!=0)g2d.draw(new Ellipse2D.Double(X+20+(yr-start)*unit - 5, Y-(res*unitY), 3, 3));
				}
			}
		}
		else if(mod.equals("hg")){
			
			g2d.setColor(Color.RED);
			for(int yr:years) {
				if(yr>=start && yr<=end) {
					m.setFilter("", yr, "", "","Summer");
					double res = m.averageHeightOfAthletes();
					//System.out.println(unitY);
					//System.out.println(Y-((res*unitY)-min_height));
					if(res!=0)g2d.draw(new Ellipse2D.Double(X+20+(yr-start)*unit - 5, Y-((res-min_height)*unitY), 3, 3));
				}
			}
			
			g2d.setColor(Color.BLUE);
			for(int yr:years) {
				if(yr>=start && yr<=end) {
					m.setFilter("", yr, "", "","Winter");
					double res = m.averageHeightOfAthletes();
					if(res!=0)g2d.draw(new Ellipse2D.Double(X+20+(yr-start)*unit - 5, Y-((res-min_height)*unitY), 3, 3));
				}
			}
		}
		else {
			
			g2d.setColor(Color.RED);
			for(int yr:years) {
				if(yr>=start && yr<=end) {
					m.setFilter("", yr, "", "","Summer");
					double res = m.averageWeightOfAthletes();
					System.out.println(res);
					if(res!=0)g2d.draw(new Ellipse2D.Double(X+20+(yr-start)*unit - 5, Y-((res-min_weight)*unitY), 3, 3));
				}
			}
			
			g2d.setColor(Color.BLUE);
			for(int yr:years) {
				if(yr>=start && yr<=end) {
					m.setFilter("", yr, "", "","Winter");
					double res = m.averageWeightOfAthletes();
					if(res!=0)g2d.draw(new Ellipse2D.Double(X+20+(yr-start)*unit - 5, Y-((res-min_weight)*unitY), 3, 3));
				}
			}
		}
		
		
		//for(int i=0;i<summer.size();i++) {
			//int yr = events.get(summer.get(i)).getYear();
			//if(yr>=start && yr<=end) {
				//g2d.drawOval(X+20+((yr-start)*unit),  Y-100 - i, 3, 3);
				//g2d.draw(new Ellipse2D.Double(X+20+(yr-start)*unit - 3, Y-100 - i - 3, 3, 3));
			//}
		//}
	}
	
	@Override
    protected void paintComponent(Graphics g) {
		
		Graphics2D g2 = (Graphics2D) g;
		//g2.draw(new Line2D.Double(X, Y, X, Y-max_Y));
		
		 g2.drawLine(X, Y, X, Y-max_Y);
		 g2.drawLine(X, Y, X+max_X, Y);
		 
		 Font font = new Font("Serif", Font.PLAIN, 6);
         g2.setFont(font);
		 
		 for(float i= 0, j = minY;i< max_Y;i+=sliceY,j+=value_slice_Y) {
			g2.draw(new Line2D.Double(X - half_I,Y - i, X + half_I , Y - i));	
			g2.drawString((int)j+"", X - half_I - 10,Y - i);
		 }
		 
		 for(float i = 20, j = start; X+i <= max_X; i += sliceX, j += value_slice_X) {
			 g2.draw(new Line2D.Double(X + i,Y - half_I, X + i , Y + half_I));	
			 g2.drawString((int)j+"", X - 10 + i,Y + half_I + 10);
		 }
		 
		 drawDots(g);
		 
		 //Graphics2D g2d = (Graphics2D)g;
		 //g2d.drawOval(X+100,  Y-100, 3, 3);
	}
	
}
