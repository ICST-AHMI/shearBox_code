import com.cycling74.max.*;
import com.cycling74.jitter.*;

public class jitcountpixels extends MaxObject
{
	int[] vec = null;
	
    public jitcountpixels(Atom[] args)
    {
		declareInlets(new int[]{DataTypes.ALL});
		declareOutlets(new int[]{DataTypes.ALL});
   	}
    
	public void jit_matrix(String inname)
	{
		int[] dim;
		int[] offset = new int[2];
		int width;
		int height;
		int planecount;
		int i,j,k,n;
		int countPixels = 0;
		JitterMatrix inmat = new JitterMatrix(inname);

		dim = inmat.getDim();
		planecount = inmat.getPlanecount();	
		// only alloc vec if size is different
		if ((vec==null)||(vec.length!=(dim[0]*planecount)))
			vec = new int[dim[0]*planecount];
					
		width = dim[0];
		height = dim[1];
		offset[0] = 0;
		
		for (i=0;i<height;i++) {
			offset[1] = i;	
			inmat.copyVectorToArray(0,offset,vec,vec.length,0);	
			if (planecount==4) {
				for (j=0,k=0;j<width;j++) {
					if(vec[k+1] > 0.f){
						countPixels++;
					}
					k = k + 4;
				}
			}
		}	
		outlet(0,"pixelcount", countPixels);
	}
}












