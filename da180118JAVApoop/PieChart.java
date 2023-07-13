package og;

import java.awt.*;
import java.awt.geom.Ellipse2D;
import java.util.Iterator;
import java.util.Map.Entry;

import javax.swing.*;

class Slice {

   double value;
   Color color;
   String name;
   public Slice(double value, Color color, String name) {  
      this.value = value;
      this.color = color;
      this.name=name;
   }
   
   public String getName() {
	   return name;
   }
}

class PieChart extends JPanel {

    private Color a = Color.RED;
    private Color b = Color.BLUE;
    private Color c = Color.YELLOW;
    Slice[] slices = new Slice[N];
    private Filter filter;
    private static int N = 6;

    public PieChart(Filter f){
    	filter = f;
    	setSlices();
    }

    private void setSlices() {
    	Iterator<Entry<String, Integer>> itr = filter.getCountCountry().entrySet().iterator();
    	int n = 0;
    	int k = 0;
    	int firstNsum = 0;
    	while(itr.hasNext()) {
    		int pom = itr.next().getValue();
			n+=pom;
			//System.out.println(itr.next());
			if(k++<N-1) {
				firstNsum+=pom;
			}
		}
    	
    	itr = filter.getCountCountry().entrySet().iterator();
    	Color r;
    	double perc;
    	for(int i=0;i<N-1;i++) {
    		r = new Color((int)(Math.random() * 0x1000000));  
    		Entry<String, Integer> nxt=itr.next();
    	    perc = (Double.valueOf(nxt.getValue())/n)*100;
    		slices[i]= new Slice(360*(perc),r,nxt.getKey());
    	}
    	r = new Color((int)(Math.random() * 0x1000000));
    	perc = (Double.valueOf((n-firstNsum))/n)*100;
    	slices[N-1]= new Slice(360*(perc),r,"Others");
    }
    
    @Override
    protected void paintComponent(Graphics g) {
        Graphics2D g2d = (Graphics2D)g;
        super.paintComponent(g2d);
        this.setBackground(new Color(255,255,255));

        g2d.setRenderingHint(RenderingHints.KEY_ANTIALIASING, RenderingHints.VALUE_ANTIALIAS_ON);

        double total = 0.0D;
        for (int i = 0; i < slices.length; i++) {
            total += slices[i].value;
        }
       

        double curValue = 90.0D;
        int startAngle = 0;

        for (int i = 0; i < slices.length; i++) {
            startAngle = (int) (curValue * 360 / total);
            int arcAngle = (int) (slices[i].value * 360 / total);
            g2d.setColor(slices[i].color);
            g2d.fillArc(20, 20, 200, 200, startAngle, arcAngle);

            g2d.setPaint(Color.BLACK);
            int x = (int)(110+100*Math.cos(((-(startAngle+(arcAngle/2)))*Math.PI)/180));
            int y = (int)(110+100*Math.sin(((-(startAngle+(arcAngle/2)))*Math.PI)/180));
            
            Font font = new Font("Serif", Font.PLAIN, 12);
            g2d.setFont(font);
            g2d.drawString(slices[i].getName(), x, y);

            curValue += slices[i].value;
        }
    }
}