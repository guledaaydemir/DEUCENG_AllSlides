import java.nio.ByteBuffer;
import java.nio.IntBuffer;
import java.util.Scanner;

public class Sort {

	public String strYour_name = "Gül Eda Aydemir";
	public long Your_number = 2015510013;
	

	public void Our_sort(int[] array, int p, int q, int digit){ 
		int q_b=q;
		int p_b=p;
		int temp= Math.abs(digit-32); //diyelimki 32. bite bakacak, stringin 0. charine bakýyor
		int count=0;
		int[] number= new int[1]; //deðiþim yapacaðý sayý.
		int[] BinaryNum = new int[32];
        boolean flag=true;
		
        while( p<q ){
			//CONVERT TO BÝNARY
			String pB=""; //pth binary number
			String qB=""; //qth binary number
			int pN= array[p];
			for(;pN > 0;count++){
				int mod = pN % 2;
				BinaryNum[count]=mod;
				pN /= 2;
			}
			for (int i = count; i < 32; i++) {
				BinaryNum[i]=0;
			}
			for (int i = BinaryNum.length-1; i >= 0; i--) {
				pB += Integer.toString(BinaryNum[i]);
			}
			count=0;
			int qN= array[q];
			for(;qN > 0;count++){
				int mod = qN % 2;
				BinaryNum[count]=mod;
				qN /= 2;
			}
			for (int i = count; i < 32; i++) {
				BinaryNum[i]=0;
			}
			for (int i = BinaryNum.length-1; i >= 0; i--) {
				qB += Integer.toString(BinaryNum[i]); 
			}
			count=0;
			//END CONVERTING

			//COMPARING
			if(pB.charAt(temp)=='1'&& qB.charAt(temp)=='0'){ // if 1 and 0 swap and q--;
				number[0]=array[p];
				array[p]=array[q];
				array[q]=number[0];
				q--;
				
			}else if(pB.charAt(temp)=='1' && qB.charAt(temp)=='1' ){
				q--;
				if(p==q){
					flag=false;
				}
			}else if(pB.charAt(temp)=='0' && qB.charAt(temp)=='0'){
				p++;
			}else if(pB.charAt(temp)=='0' && qB.charAt(temp)=='1'){
				q--;
			}
			//END COMPARING
		}
		//RECURSIVE
		if((digit-1) > 0 && flag==false && q_b-q!=0 && p-1-p_b!=0 ){ // 1-1 and p==q situation
			Our_sort(array, p_b, p-1, digit-1);
			Our_sort(array, q, q_b, digit-1);
		}
		else if((digit-1) > 0 && q_b-q+1!=0 && p-p_b!=0){
			Our_sort(array, p_b, p, digit-1);
			Our_sort(array, q+1, q_b, digit-1);
		}
		//END RECURSIVE
	}



	public void printArray(int[]array){
		for (int i = 0; i < array.length; i++) {	
			System.out.print(array[i]+ " ");}
		System.out.println();
	}

}
