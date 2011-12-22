import java.awt.*;
import javax.swing.*;


import java.awt.event.*;

@SuppressWarnings("serial")
public class SwingApplication extends JFrame  {
	PointSet pointSetT;
	PointCanvas pointCanvas;
	EditTDialog editTDialog;
	ResultDialog resultDialog;
	
    public SwingApplication() {
        super("Лабораторная работа 3");
        setSize(350, 350);
        setDefaultCloseOperation(EXIT_ON_CLOSE);
         
        // Creates a menubar for a JFrame
        JMenuBar menuBar = new JMenuBar();
        
        // Add the menubar to the frame
        setJMenuBar(menuBar);
        
        // Define and add two drop down menu to the menubar
        JMenu fileMenu = new JMenu("File");
        JMenu helpMenu = new JMenu("Help");
        menuBar.add(fileMenu);
        menuBar.add(helpMenu);
        
        // Create and add simple menu item to one of the drop down menu
        JMenuItem newAction = new JMenuItem("New");
        JMenuItem viewAction = new JMenuItem("View Points...");
        JMenuItem resultAction = new JMenuItem("View Results...");
        JMenuItem exitAction = new JMenuItem("Exit");
        JMenuItem aboutAction = new JMenuItem("About...");
        
        // Create and add CheckButton as a menu item to one of the drop down
        // menu
        JCheckBoxMenuItem checkAction = new JCheckBoxMenuItem("Check Action");
        
        fileMenu.add(newAction);
        fileMenu.add(viewAction);
        fileMenu.add(resultAction);
        fileMenu.add(checkAction);
        fileMenu.addSeparator();
        fileMenu.add(exitAction);
        helpMenu.add(aboutAction);
        // Add a listener to the menu items. actionPerformed() method will be
        // invoked, if user triggred this menu item
        exitAction.addActionListener(new ActionListener() {
        	public void actionPerformed(ActionEvent ae){
				System.exit(0);
			}
        });
        viewAction.addActionListener(new ActionListener() {
        	public void actionPerformed(ActionEvent ae){
        		editTDialog.actualize();
        		editTDialog.setVisible(true);
        		pointSetT.findAll();
				pointCanvas.repaint();
        		
			}
        });
        resultAction.addActionListener(new ActionListener() {
        	public void actionPerformed(ActionEvent ae){
				resultDialog.actualize();
				resultDialog.setVisible(true);        		
			}
        });
        checkAction.addActionListener(new ActionListener() {
        	public void actionPerformed(ActionEvent ae){
        		pointSetT.showResult=!pointSetT.showResult;
        		pointSetT.findAll();
				pointCanvas.repaint();
        	}
        });
        
        pointSetT= new PointSet(20);
        editTDialog=new EditTDialog("Изменить множество T",this,pointSetT);
		resultDialog=new ResultDialog("Результат",this,pointSetT);
		pointCanvas = new PointCanvas(pointSetT);
		pointCanvas.setBounds(0,0,1000,500);
		this.add(pointCanvas);
		pointCanvas.addMouseListener(new MouseListener(){
			@Override
			public void mouseClicked(MouseEvent e) {
				if(e.getButton()==e.BUTTON1){
					pointSetT.add(e.getX(),e.getY());
				}
				pointSetT.findAll();
				pointCanvas.repaint();
			}
			@Override
			public void mouseEntered(MouseEvent arg0) {
			}
			@Override
			public void mouseExited(MouseEvent arg0) {
			}
			@Override
			public void mousePressed(MouseEvent arg0) {
			}
			@Override
			public void mouseReleased(MouseEvent arg0) {
			}
		});
		
		
    }
    /*@Override
	public void actionPerformed(ActionEvent ae) {
		int row = table.getSelectedRow();
		int col = table.getSelectedColumn();
		String s = (String) table.getValueAt(row, col);
		jtf.setText(s);
	}*/
    public static void main(String[] args) {
        SwingUtilities.invokeLater(new Runnable() {
            public void run() {
            	SwingApplication ex = new SwingApplication();
                ex.setVisible(true);
            }
        });
    }
    
    class PointCanvas extends Canvas
	{
		PointSet ps;
		PointCanvas(PointSet ps)
		{
			super();
			this.ps=ps;
		}
		public void paint(Graphics gra)
		{
			Graphics2D g = (Graphics2D)gra;
			BasicStroke pen1 = new BasicStroke(1); 
			BasicStroke pen3 = new BasicStroke(3); 
			
			g.setFont(new Font("SansSerif", Font.PLAIN, 14));
			
			g.setColor(Color.white);
			g.fillRect(0,0,this.getWidth(),this.getHeight());
			
			g.setStroke(pen1);
			
			g.setColor(Color.yellow);
			for(int i=0; i< ps.circleCount; ++i)
			{
				g.drawOval((int)(ps.centerx[i]-ps.radius[i]),(int)(ps.centery[i]-ps.radius[i]),(int)(2*ps.radius[i]),(int)(2*ps.radius[i]));
			}
			if(ps.bestIn>0)
			{
				g.setStroke(pen3);
				g.setColor(Color.green);
				g.drawOval((int)(ps.centerx[ps.bestCircle]-ps.radius[ps.bestCircle]),(int)(ps.centery[ps.bestCircle]-ps.radius[ps.bestCircle]),
						   (int)(2*ps.radius[ps.bestCircle]),(int)(2*ps.radius[ps.bestCircle]));
				g.setStroke(pen1);
			}
			
			
			g.setColor(Color.black);
			for(int i=0; i< ps.pointCount; ++i)
			{
				if(ps.mark[i]==0)
				{
					g.drawRect(ps.xkor[i]-2,ps.ykor[i]-2,5,5);
				}
			}
		}
	}
    
    class EditTDialog extends JDialog 
	{
	PointSet ps;
	Object[][] data;
	JTable table;
	String[] colHeads = {"n" ," x ", " y "};
	JScrollPane jsp; 
	int n;  
	EditTDialog (String str, Frame parent,PointSet ps1) 
	{
		super (parent, str,true);
		setSize(300,400);
		setResizable(false);
		Container contPane = getContentPane();
		contPane.setLayout(new FlowLayout());
		ps=ps1;
		jsp = new JScrollPane(table,ScrollPaneConstants.VERTICAL_SCROLLBAR_AS_NEEDED,ScrollPaneConstants.HORIZONTAL_SCROLLBAR_AS_NEEDED);
		jsp.setPreferredSize(new java.awt.Dimension(250, 250));
		actualize();
		
		JButton jbtAdd = new JButton(" + ");
	
		jbtAdd.addActionListener(new AddListener());
		JButton jbtDel = new JButton(" - ");
	
		jbtDel.addActionListener(new DelListener());
		JButton jbtOk = new JButton("   Ок   ");
		jbtOk.addActionListener(new OkListener());
		
		
		contPane.add(new JLabel("Points: "));
		contPane.add(jsp);
		contPane.add(new JLabel(""));
		contPane.add(jbtAdd);
		contPane.add(new JLabel("   "));
		contPane.add(jbtDel);
		contPane.add(new JLabel("                                                                         "));
		contPane.add(jbtOk);
		
		addWindowListener (new WindowAdapter()
		{
			public void windowClosing(WindowEvent ie)
			{
				dispose();
			}
		});
	}
	void actualize()
	{
		n=0;
		data=new Object[ps.pointCount-ps.markCount][3];
		for(int i=0, j=0; i<ps.pointCount; ++i)
		{
			if(ps.mark[i]==0)
			{
				data[j][0]=i;
				data[j][1]=ps.xkor[i];
				data[j][2]=ps.ykor[i];
				++j;
				++n;
			}
		}
		table = new JTable(data, colHeads);
		table.setRowSelectionAllowed(true);
		jsp.getViewport().setView(table);
	}
	class AddListener implements ActionListener
	{
		public void actionPerformed(ActionEvent ae)
		{
			ps.add(0,0);
			actualize();
		}
	}
	class DelListener implements ActionListener
	{
		public void actionPerformed(ActionEvent ae)
		{
			//удаление точки
		    int deln=table.getSelectedRow();
		    --n;
		    Object[][] data1 = new Object[n][3]; 
		    System.arraycopy(data,0,data1,0,deln);
		    System.arraycopy(data,deln+1,data1,deln,data.length-deln-1);
		    data=data1;
		    table = new JTable(data, colHeads);
		    jsp.getViewport().setView(table);
		}
	}

		class OkListener implements ActionListener
		{
			public void actionPerformed(ActionEvent ae)
			{	
				for(int i=0; i<ps.size; ++i)
				{
					ps.mark[i]=-1;
				}
				ps.pointCount=0;
				ps.markCount=0;
				int j=0;
				for(int i=0; i<n; ++i)
				{
					j=Integer.parseInt(data[i][0].toString());
					ps.mark[j]=0;
					ps.xkor[j]=Integer.parseInt(data[i][1].toString());
					ps.ykor[j]=Integer.parseInt(data[i][2].toString());
				}
				ps.pointCount=j+1;
				for(int i=0; i<ps.pointCount; ++i)
				{
					if(ps.mark[i]==-1)
					{
						++ps.markCount;
					}
				}
				ps.circleCount=0;
				ps.bestIn=-1;
				dispose();
			}
		}
	}
    class ResultDialog extends JDialog 
	{
	PointSet ps;
	Object[][] data;
	JTable table;
	String[] colHeads = {"n", "x" ," y ", " r " ,"c"};
	JScrollPane jsp; 
	int n;  
	JLabel jlb;
	ResultDialog (String str, Frame parent,PointSet ps1) 
	{
		super (parent, str,true);
		setSize(310,460);
		setResizable(false);
		jlb=new JLabel("Best circle:" + ps1.bestCircle);
		Container contPane = getContentPane();
		contPane.setLayout(new FlowLayout());
		ps=ps1;
		n=0;
		data=new Object[ps.circleCount][5];
		
		table = new JTable(data, colHeads);
		table.setCellSelectionEnabled(false);
		table.setRowSelectionAllowed(false);
		jsp = new JScrollPane(table,ScrollPaneConstants.VERTICAL_SCROLLBAR_AS_NEEDED,ScrollPaneConstants.HORIZONTAL_SCROLLBAR_AS_NEEDED);
		jsp.setPreferredSize(new java.awt.Dimension(250, 320));
		jsp.getViewport().setView(table);
		
	
		JButton jbtOk = new JButton("   Ок   ");
		jbtOk.addActionListener(new OkListener());

		contPane.add(jlb);
		contPane.add(new JLabel("                                                                         "));
		contPane.add(new JLabel("Circles: "));
		contPane.add(new JLabel("        "));
		contPane.add(jsp);
		contPane.add(new JLabel("                                                                                "));
		contPane.add(jbtOk);
	

	
		addWindowListener (new WindowAdapter()
		{
			public void windowClosing(WindowEvent ie)
			{
				dispose();
			}
		});
	}
	void actualize()
	{
		n=0;
		data=new Object[ps.circleCount][5];
		for(int i=0, j=0; i<ps.circleCount; ++i)
		{
				data[j][0]=i;
				data[j][1]=ps.centery[i];
				data[j][2]=ps.centery[i];
				data[j][3]=ps.radius[i];
				data[j][4]=ps.circleIn[i];
				++j;
				++n;
	
		}
		table = new JTable(data, colHeads);
		jsp.getViewport().setView(table);
		jlb.setText("Best circle:" + ps.bestCircle);
	}
	
	

		class OkListener implements ActionListener
		{
			public void actionPerformed(ActionEvent ae)
			{			
				dispose();
			}
		}
	
	}
    class PointSet
    {
    	public boolean showResult;
		int [] xkor;
    	int [] ykor;
    	int [] mark;
    	int pointCount;
    	int markCount;
    	int size;
    	int bestIn;
    	int bestCircle;
    	
    	
    	
    	double [] centerx;
    	double [] centery;
    	double [] radius;
    	int [ ] circleIn;
    	int [] circleInSelf;
    	int [] circleInOther;
    	int circleCount;
    	
        double eps;
    	
    	
    	PointSet(int size1)
    	{
    		size=size1;
    		eps=1;
    		pointCount=0;
    		circleCount=0;
    		xkor = new int [size];
    		ykor = new int [size];
    		mark = new int [size];
    		centerx = new double [size*size*size];
    		centery = new double [size*size*size];
    		radius = new double [size*size*size];
    		circleIn = new int [size*size*size];
    		bestCircle=-1;
    		bestIn=-1;
    		for(int i=0; i<size; ++i)
    		{
    			mark[i]=-1;
    		}
    		markCount=0;
    		showResult=false;
    	}
    	void find(int i1, int i2, int i3)
    	{
    		 double x1,x2,x3,y1,y2,y3;
    		 double x,y,r;
    		 x1=(xkor[i1]+xkor[i2])/2.0;//подсчёт промежуточных переменных
    		 y1=(ykor[i1]+ykor[i2])/2.0;
    		 x2=xkor[i2]*1.0;
    		 y2=ykor[i2]*1.0;
    		 x3=(xkor[i2]+xkor[i3])/2.0;
    		 y3=(ykor[i2]+ykor[i3])/2.0;
    		 x=((y1-y3)*(y1-y2)*(y3-y2)+x1*(x1-x2)*(y3-y2)-x3*(y1-y2)*(x3-x2))/
    		                                             ((x1-x2)*(y3-y2)-(y1-y2)*(x3-x2));
    		 y=((x1-x3)*(x1-x2)*(x3-x2)+y1*(y1-y2)*(x3-x2)-y3*(x1-x2)*(y3-y2))/
    		                                             ((y1-y2)*(x3-x2)-(x1-x2)*(y3-y2));
    		 r=Math.sqrt((x-x2)*(x-x2)+(y-y2)*(y-y2));//подсчёт координат центра и радиуса
    		 for(int i=0; i<circleCount; ++i)
    		 {
    		 	if(centerx[i]==x && centery[i]==y && radius[i]==r )
    		 	{
    		 		return;
    		 	}
    		 }
    		 centerx[circleCount]=x;  //возвращение значений через параметры
    		 centery[circleCount]=y;
    		 radius[circleCount]=r;
    		 circleIn[circleCount]=0;
    		 for(int i=0; i<pointCount; ++i)
    		 {
    		 	if(Math.abs((x-xkor[i])*(x-xkor[i])+(y-ykor[i])*(y-ykor[i])-r*r)<=eps)
    		 	{
    		 		++circleIn[circleCount];
    		 	}
    		 	
    		 }
    		  ++circleCount;
    	}
    	int checkCol(int i1, int i2, int i3)
    	{
    		double s=xkor[i1]*ykor[i2]-xkor[i2]*ykor[i1]-xkor[i1]*ykor[i3]+xkor[i3]*ykor[i1]+xkor[i2]*ykor[i3]-xkor[i3]*ykor[i2];
    		if(Math.abs(s/2.0)<eps*eps)
    		{
    			return 0;
    		}
    		return 1;
    	} 
    	public void findAll()
    	{
    		bestIn=-1;
    		circleCount=0;
    		if(showResult)
    		for(int i=0; i<pointCount; ++i)
    		{
    			for(int j=0; j<i; ++j)
    			{
    				for(int k=0; k<j; ++k)
    				{
    					if(checkCol(i,j,k)==1)
    					{
    						if(mark[i]>-1 && mark[j]>-1 && mark[k]>-1 )
    						{
    							find(i,j,k);
    							if(bestIn<circleIn[circleCount-1])
    							{
    								bestIn=circleIn[circleCount-1];
    								bestCircle=circleCount-1;
    							}
    						}
    					}
    				}
    			}
    		}
    	}
    	public void add(int x, int y)
    	{
    		if(pointCount<=size)
    		{
    			int i;
    			for(i=0;i<pointCount;++i)
    			{
    				if(mark[i]==-1)
    				{
    					break;
    				}
    			}
    			if(i==size)
    			{
    				 return;
    			}
    			xkor[i]=x;
    			ykor[i]=y;
    			mark[i]=0;
    			if(i==pointCount) pointCount++;
    			else markCount--;
    			
    			bestIn=-1;
    			circleCount=0;
    		}
    	}
    	public void del(int point)
    	{
    		mark[point]=-1;
    		markCount++;
    		bestIn=-1;
    		circleCount=0;
    	}
    }
}
