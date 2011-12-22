import java.awt.*;
import java.awt.event.*;

public class GrafApplication {
	public static void main(String[] args) {
		ОсновноеОкно gf = new ОсновноеОкно("Граф");
		gf.setSize(600, 400);
		gf.setVisible(true);
	}
}

class Параметры {
	int вершинаA, вершинаD;
	int реброB, реброC;
	boolean корректность=false;
	void проверитьКорректность(int n)
	{
		if(вершинаA>n||вершинаD>n||реброB>n||реброC>n) корректность=false;
	}
}

class ДиалогПараметры extends Dialog {
	Параметры params;
	TextField pt1, pt2, ln1, ln2;
	public ДиалогПараметры(final Параметры params, Frame parent, String title){
		super(parent,title,true);
		this.params=params;
		setLayout(new GridLayout(3,3,10,5));
		setSize(400,120);
		Button btOk=new Button("Ок"), btCancel=new Button("Отмена");
		Label lbPoints=new Label("Вершины:"), lbLine=new Label("Ребро между вершинами:");
		pt1=new TextField();
		pt2=new TextField();
		ln1=new TextField();
		ln2=new TextField();
		add(lbPoints);add(pt1);add(pt2);
		add(lbLine);add(ln1);add(ln2);
		add(btOk);add(btCancel);
		btOk.addActionListener(new ActionListener(){
			public void actionPerformed(ActionEvent ev) throws NumberFormatException {
				params.вершинаA = Integer.parseInt(pt1.getText());
				params.вершинаD = Integer.parseInt(pt2.getText());
				params.реброB = Integer.parseInt(ln1.getText());
				params.реброC = Integer.parseInt(ln2.getText());
				params.корректность=true;
				dispose();
				setVisible(false);
			}
		});
		btCancel.addActionListener(new ActionListener(){
			public void actionPerformed(ActionEvent ev){
				dispose();
				setVisible(false);
			}
		});
		
	}
}

class ОсновноеОкно extends Frame implements ActionListener, MouseListener, ComponentListener {
	Параметры параметры;
	Граф граф;
	Холст холст;
	int вершинаНовогоРебра=-1;
	Label статуснаяСтрока;
	
	public ОсновноеОкно(String title) {
		super(title);
		параметры = new Параметры();
		addWindowListener(new WindowAdapter(){
			public void windowClosing(WindowEvent we){
				System.exit(0);
			}
		});
		addMouseListener(this);
		addComponentListener(this);
		setLayout(new BorderLayout());
		статуснаяСтрока=new Label("Задайте граф");
		статуснаяСтрока.setBackground(new Color(242,242,242));
		add(статуснаяСтрока,BorderLayout.SOUTH);
		граф = new Граф();
		MenuBar mb = new MenuBar();
		Menu файл = new Menu("Файл");
		MenuItem новыйГраф = new MenuItem("Новый граф");
		файл.add(новыйГраф);
		MenuItem выход = new MenuItem("Выход");
		файл.add(выход);
		mb.add(файл);
		
		Menu опции = new Menu("Опции");
		MenuItem параметр = new MenuItem("Параметры...");
		опции.add(параметр);
		MenuItem задание = new MenuItem("Задание...");
		опции.add(задание);
		mb.add(опции);
		
		setMenuBar(mb);
		выход.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent ae) {
				System.exit(0);
			}
		});
		final ОсновноеОкно f=this;
		параметр.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent ae) {
				Dialog pd = new ДиалогПараметры(параметры, f,"Параметры...");
				pd.setVisible(true);
				параметры.проверитьКорректность(граф.количествоВершин);
				f.repaint();
			}
		});
		задание.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent ae) {
				статуснаяСтрока.setText("Найти цикл, проходящий через вершины a и d и ребро b c");
			}
		});
		новыйГраф.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				граф.очистить();
	            параметры.корректность=false;
				f.repaint();
			}
		});
	}
	public void actionPerformed(ActionEvent ev) {
		repaint();
	}
	public void componentResized(ComponentEvent e) {
		repaint();
	}
	public void paint(Graphics g){
		if (граф.количествоВершин==0) return;
		холст = new Холст(граф.количествоВершин, this.getWidth(), this.getHeight() - 70, g);

		double a=0;
		for(int j=0;j<граф.количествоВершин;j++)
		 {
           for (int k=0;k<граф.количествоВершин;k++)
           if(граф.естьРебро(j,k))
               холст.соединитьВершины(j,k);
           a+=холст.step;
		 }
		if(параметры.корректность)
		 {  
			g.setColor(Color.yellow);
			if(граф.поиск_в_глубину(холст,параметры.вершинаA,параметры.реброB,параметры.реброC,параметры.вершинаD))
				this.статуснаяСтрока.setText("Цикл найден.");
			else this.статуснаяСтрока.setText("Нет таких циклов.");
			g.setColor(Color.black);
		 }
		for(int j=0;j<граф.количествоВершин;j++)
           холст.нарисоватьВершину(j);
	}
	
	public void mouseClicked(MouseEvent arg0) {}
	public void mouseEntered(MouseEvent arg0) {}
	public void mouseExited(MouseEvent arg0) {}
	public void mousePressed(MouseEvent e) {
		if (граф.количествоВершин==0) { граф.новаяВершина(); this.repaint(); return; }
        int выделеннаяВершина = холст.вершинаПоXY(e.getX(), e.getY());
        if (выделеннаяВершина == -1) { граф.новаяВершина(); this.repaint(); }
        вершинаНовогоРебра = выделеннаяВершина;
	}
	public void mouseReleased(MouseEvent e) {
		if (граф.количествоВершин == 0) { граф.новаяВершина(); this.repaint(); return; }
        int выделеннаяВершина = холст.вершинаПоXY(e.getX(), e.getY());
        if (выделеннаяВершина != -1 && вершинаНовогоРебра != -1) граф.новоеРебро(выделеннаяВершина, вершинаНовогоРебра);
        this.repaint();
        вершинаНовогоРебра=-1;
	}
	public void componentHidden(ComponentEvent arg0) {}
	public void componentMoved(ComponentEvent arg0) {}
	public void componentShown(ComponentEvent arg0) {}
}
class Холст 
{
	private int cx,cy;//центр холста
    private int n,r,R;//количество вершин графа, радиус вершины, радиус окружности задающей центры вершин
    public double step;//шаг радиуса R для перехода к следующей вершине
	private Graphics g;
	private final int st=40;//отступ сверху
	
    public Холст(int n, int mx, int my, Graphics g)
    {
        this.n = n;
        this.cx = mx / 2;
        this.cy = my / 2;
        int rr=(cx<cy?cx:cy);
        int bb=(rr/n)>>1;
        this.R = (int)(rr / (1 + Math.sin(Math.PI / n)));
        this.r = rr - R - bb;
		if(r<0)r=-r;
        this.step = 2 * Math.PI / n;
        this.g = g;
    }
    private void линия(int x,int y,int xx,int yy)
    {
		g.drawLine(x,st+y,xx,st+yy);
    }
    public void соединитьВершины(int i,int j)
    {
        int x = (int)(cx + R * Math.cos(step * j)), y = (int)(cy + R * Math.sin(step * j));
        int xx = (int)(cx + R * Math.cos(step * i)), yy = (int)(cy + R * Math.sin(step * i));
        линия(x,y,xx,yy);
    }
    public void нарисоватьВершину(int j)
    {
            int x=(int)(cx+R*Math.cos(step*j)), y=(int)(st+cy+R*Math.sin(step*j));
			g.setColor(Color.white);
            g.fillOval(x-r,y-r,2*r,2*r);
			g.setColor(Color.black);
            g.drawOval(x-r,y-r,2*r,2*r);
			String s= String.valueOf(j);
			int dx=3*(j>9?2:1), dy=-4;
			g.drawString(s,x-dx,y-dy);
    }
    public int вершинаПоXY(int X, int Y)
    {
    	int res = -1;
    	double a = 0;
        for (int j = 0; j < n; j++)
        {
            int x = (int)(cx + R * Math.cos(a)), y = (int)(st+cy + R * Math.sin(a));
            if ((X - x) * (X - x) + (Y - y) * (Y - y) <= r * r)
                res = j;
            a += step;
        }
        return res;
    }
}
class Граф
{
    private boolean[][] матрицаCмежности=new boolean[100][100];  //use: contact[max(i,j),min(i,j)]
    public int количествоРебер;
    
    public int количествоВершин;
    public void очистить() {for(int i =0;i<100;++i) for(int j =0;j<100;++j) матрицаCмежности[i][j]=false; количествоВершин=0;количествоРебер=0;}
	public Граф() { очистить(); }
    public void новоеРебро(int a, int b) { матрицаCмежности[a>b?a:b][a>b?b:a]=true;количествоРебер++; }
    public boolean естьРебро(int a, int b){ return матрицаCмежности[a>b?a:b][a>b?b:a]; }
    public int новаяВершина() {return количествоВершин++;}
    // Найти самый длинный цикл через вершины а d и ребро b c
    private int[] пройдено = new int[100];
    public boolean поиск_в_глубину(Холст холст,int a, int b, int c, int d)
    {
            int максимальная_длина=0;
            for(int i=0;i<100;i++)
                    пройдено[i]=-1;
            int[] очередь = new int[100];
            пройдено[a]=-2;
            int текущая_вершина=a;
            очередь[0]=a;
            int текущая_длина=1;
            int следующая_вершина=0;
            int[] цикл = new int[1];
			boolean ребро_пройдено=false;
			do
            {
                    if(следующая_вершина<количествоВершин)
                    for(;следующая_вершина<количествоВершин;следующая_вершина++)
                    if(естьРебро(текущая_вершина,следующая_вершина)) break;
                    if(следующая_вершина<количествоВершин)
                    {
                            if(пройдено[следующая_вершина]==-1)
                            {
                                    // шаг вперед
                                    очередь[текущая_длина++]=текущая_вершина;
                                    пройдено[следующая_вершина]=текущая_вершина;
                                    текущая_вершина=следующая_вершина;
                                    следующая_вершина=-1;
                                    if (текущая_вершина == b && пройдено[c] == -1 && естьРебро(b,c)) 
                                    { 
                                        ребро_пройдено = true; 
                                        очередь[текущая_длина++] = текущая_вершина; 
                                        пройдено[c] = текущая_вершина; 
                                        текущая_вершина = c; 
                                    }
                                    else
                                        if (текущая_вершина == c && пройдено[b] == -1 && естьРебро(c, b)) 
                                        { 
                                            ребро_пройдено = true; 
                                            очередь[текущая_длина++] = текущая_вершина; 
                                            пройдено[b] = текущая_вершина; текущая_вершина = b; 
                                        }
                            }
							if(следующая_вершина==a&&пройдено[d]!=-1&&ребро_пройдено&&максимальная_длина<текущая_длина)
                            {
                                максимальная_длина = текущая_длина;
                                
                                цикл = new int[максимальная_длина + 1];
                                int s=0;
								for(int l=текущая_вершина;l!=-2;l=пройдено[l])
								{
                                    цикл[s] = l;
                                    s++;
								}
                                цикл[s] = текущая_вершина;
							}
                            следующая_вершина++;
                    }
                    else //ничего не найдено
                    {
                            // шаг назад
                            пройдено[текущая_вершина]=-1;
                            следующая_вершина=текущая_вершина+1;
                            if(текущая_вершина==c&&очередь[текущая_длина-1]==b||текущая_вершина==b&&очередь[текущая_длина-1]==c)
								ребро_пройдено=false;
							текущая_вершина=очередь[--текущая_длина];
                    }
            }
            while (текущая_длина>0);
            if (максимальная_длина == 0) return false;
            for (int l = 0; l < максимальная_длина; l++)
                холст.соединитьВершины(цикл[l], цикл[l+1]);
            return true;
    }
}