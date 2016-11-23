package interview.SonarSource;

import java.io.File;
import java.io.FileNotFoundException;
import java.math.BigInteger;
import java.util.Scanner;


public class SolutionTask1 {

	   
	static SolutionTask1 sol = new SolutionTask1();
    
    public static void main(String[] args) throws FileNotFoundException {
    	
    	File file = new File("./TEST/interview/SonarSource/input-test2.txt");
    	Scanner in = new Scanner(file);
    	// Scanner in = new Scanner(System.in);

 		// creating the set of nodes of the undirected graph
		int A = in.nextInt();
		int B = in.nextInt();
		 		
    	
    	System.out.println(solution(A, B));
 		
    }
    
    private static int solution(int A, int B) {
    	
    	 BigInteger mul = new BigInteger(Integer.toString(A));
         BigInteger valB = new BigInteger(Integer.toString(B));
         BigInteger valTwo = new BigInteger(Integer.toString(2));
         int res = 0, sum = 0;
         
         mul = mul.multiply(valB);

         while(mul.longValue() > 0){
        	 res = mul.remainder(valTwo).intValue();
        	 
        	 if(res == 1)
        		 sum++;
        	 
        	 mul = mul.divide(valTwo);
        	 
         }
    	
    	return sum;
	}
    
}
