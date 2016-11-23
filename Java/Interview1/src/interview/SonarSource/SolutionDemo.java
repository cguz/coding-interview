package interview.SonarSource;

import java.io.File;
import java.io.FileNotFoundException;
import java.util.Scanner;


public class SolutionDemo {

	   
	static SolutionDemo sol = new SolutionDemo();
    
    public static void main(String[] args) throws FileNotFoundException {
    	
    	File file = new File("./TEST/interview/SonarSource/input-test.txt");
    	Scanner in = new Scanner(file);
    	// Scanner in = new Scanner(System.in);

 		// creating the set of nodes of the undirected graph
 		int N = in.nextInt();
 		
    	int[] board = new int[N];
    	for(int i=0; i < N;++i){
    		board[i] = in.nextInt();
    	}
    	
    	System.out.println(equi_efficient(board));
 		
    }
    
    /**
     * it fails on large input values (for example if the input array contains 
     * values like MIN/MAX_INT) due to the arithmetic overflows - BIGINTEGER
     * @param A
     * @return
     */
    private static int solution(int[] A) {
    	
    	int[] total = new int[A.length];
    	
    	total[A.length-1] = A[A.length-1];
    	for(int i=A.length-2; i >=0; i--){
    		total[i] = A[i] + total[i+1];
    	}
    	
    	int sum = 0;
    	for(int i=0; i < A.length; ++i){
    		sum+=A[i];
    		if((sum == 0 || sum == A.length-1) && (i+2 == A.length))
    			return i+1;
    		
    		if(sum == total[i+2])
    			return i+1;
    	}
    	
    	return -1;
	}
    
    static int equi( int A[]) {
    	int n = A.length;
        int k, m, lsum, rsum; 
        for(k = 0; k < n; ++k) { 
            lsum = 0; rsum = 0;
            for(m = 0; m < k; ++m) lsum += A[m]; 
            for(m = k + 1; m < n; ++m) rsum += A[m];  
            if (lsum == rsum) return k;
        } 
        return -1; 
    }
    
    static int equi_efficient(int arr[]) {
    	int n = arr.length;
        if (n==0) return -1; 
        long sum = 0;
        int i; 
        for(i=0;i<n;i++) sum+=(long) arr[i]; 

        long sum_left = 0;    
        for(i=0;i<n;i++) {
            long sum_right = sum - sum_left - (long) arr[i];
            if (sum_left == sum_right) return i;
            sum_left += (long) arr[i];
        } 
        return -1; 
    } 
}
