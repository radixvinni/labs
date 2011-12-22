public class SparseMatrixTest {
  public static void main(String args[]) {
  
  SparseMatrix mySparseMatrix = new SparseMatrix( 10, 10 );   
  SparseMatrix another = new SparseMatrix( 8, 12 );   
  try{
  for (int i=1;i<=10;i++)
   {
    mySparseMatrix.setElement( i, i, 1 );  
   }
  mySparseMatrix.setElement( 4, 3, 6 );
  System.out.println(mySparseMatrix.getElement(3, 3));
  System.out.println(mySparseMatrix.getElement(4, 3));
  //System.out.println(mySparseMatrix.getElement(4, 12));
  
  System.out.println("До прибавления:");
  mySparseMatrix.print();
  
  for(int i=2; i<8;i++)
	  for(int j=i/2;j<12-i/2;j++)
		  another.setElement(i, j, i+j);
  
  System.out.println("После прибавления:");
  mySparseMatrix.add(another);
  mySparseMatrix.print();
  System.out.println("");
  
  SparseMatrix a = new SparseMatrix(1,1);
  SparseMatrix b = new SparseMatrix(1,1);
  a.setElement(0, 0, 2);
  a.setElement(0, 1, 3);
  a.setElement(1, 0, 3);
  a.setElement(1, 1, 4);
  b.setElement(0, 0, 2);
  b.setElement(0, 1, 3);
  b.setElement(1, 0, 3);
  b.setElement(1, 1, 4);
  System.out.println("Матрица а:");
  a.print();
  System.out.println("Матрица b:");
  b.print();
  System.out.println("Их произведение:");
  a.mul(b).print();
  }
  catch(Exception e){
	  System.out.println(e.toString());
  }
  }
};

class SparseMatrix {
   class MatrixElement{
	   int i, j;
	   int value;
	   MatrixElement left, right, top, bottom;
	   public MatrixElement(int i, int j, int value) {
		   this.i=i;
		   this.j=j;
		   this.value=value;
	   }
   }
   int imax, jmax;
   public SparseMatrix(int imax, int jmax) {        
      this.imax=imax;
      this.jmax=jmax;
   }
   MatrixElement first=null;
   
   public void setElement(int i, int j, int val) throws Exception {
	if(i>imax) throw new Exception("Out of range");
	if(j>jmax) throw new Exception("Out of range");
	if(first==null) {
		first=new MatrixElement(i,j,val);
		return;
	}
	MatrixElement c = first;
	if(c.i>i){
		while(c.i>i && c.top!=null) c=c.top;
	}
	else {
		while(c.i<i && c.bottom!=null) c=c.bottom;
	}
	if(c.i>i){
		MatrixElement d = new MatrixElement(i, c.j, 0);
		d.top=c.top;
		c.top=d;
		d.bottom=c;
		if(d.top!=null)d.top.bottom=d;
		c = c.top;
	} else
	if(c.i<i) {
		MatrixElement d = new MatrixElement(i, c.j, 0);
		d.bottom=c.bottom;
		c.bottom=d;
		d.top=c;
		if(d.bottom!=null)d.bottom.top=d;
		c = c.bottom;
	}
	if(c.j>j){
		while(c.j>j && c.left!=null) c=c.left;
	}
	else {
		while(c.j<j && c.right!=null) c=c.right;
	}
	if(c.j>j) {
		MatrixElement d = new MatrixElement(i, j, val);
		d.left=c.left;
		c.left=d;
		d.right=c;
		if(d.left!=null)d.left.right=d;
		return;
	} else
	if(c.j<j) {
		MatrixElement d = new MatrixElement(i, j, val);
		d.right=c.right;
		c.right=d;
		d.left=c;
		if(d.right!=null)d.right.left=d;
		return;
	}
	c.value=val;
   }
   
   int getElement(int i, int j) throws Exception {
	   	if(i>imax) throw new Exception("Out of range");
		if(j>jmax) throw new Exception("Out of range");
		MatrixElement c = first;
		if(c.i>i){
			while(c.i>i && c.top!=null) c=c.top;
			if(c.i!=i){
				return 0;
			}
		}
		else {
			while(c.i<i && c.bottom!=null) c=c.bottom;
			if(c.i!=i) {
				return 0;
			}
		}
		if(c.j>j){
			while(c.j>j && c.left!=null) c=c.left;
			if(c.j!=j) {
				return 0;
			}
		}
		else {
			while(c.j<j && c.right!=null) c=c.right;
			if(c.j!=j) {
				return 0;
			}
		}
		return c.value;
   }
   void add(SparseMatrix a){
	   if (a.imax>imax) imax=a.imax;
	   if (a.jmax>jmax) jmax=a.jmax;
	   for(int i=0;i<=imax;i++)
		   for(int j=0;j<=jmax;j++)
		   try{
			   if(a.getElement(i, j)!=0){
			   setElement(i, j, getElement(i, j)+a.getElement(i, j));
			   }
		   } catch(Exception e) {}
	   }
   void sub(SparseMatrix a){
	   if (a.imax>imax) imax=a.imax;
	   if (a.jmax>jmax) jmax=a.jmax;
	   for(int i=0;i<=imax;i++)
		   for(int j=0;j<=jmax;j++)
			   try {
				   if(a.getElement(i, j)!=0){
					   setElement(i, j, getElement(i, j)-a.getElement(i, j));
				   }
			   } catch (Exception e) {}
	   }
   void print(){
	   for(int i=0;i<=imax;i++){
		   for(int j=0;j<=jmax;j++)
			   try {System.out.print(getElement(i, j)+"\t"); } catch(Exception e) {}
	   System.out.println();
	   }
   }
   SparseMatrix mul(SparseMatrix a) throws Exception
   {
	   if(jmax!=a.imax) throw new Exception("Out of range");
	   SparseMatrix mul = new SparseMatrix(imax,a.jmax);
	   for(int i=0;i<=imax;i++)
		   for(int j=0;j<=a.jmax;j++)
		   {
			   int val = 0;
			   for (int k=0;k<=jmax;k++){
				   val+=getElement(i, k)*a.getElement(k,j);
			   }
			   if(val!=0) mul.setElement(i, j, val);
		   }
	   return mul;
   }
};
 
