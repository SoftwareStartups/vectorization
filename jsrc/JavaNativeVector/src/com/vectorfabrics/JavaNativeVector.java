/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

package com.vectorfabrics;

/**
 *
 * @author Jos
 */
public class JavaNativeVector {

    /**
     * @param args the command line arguments
     */
    public static void main(String[] args) {
        vectorizeLib veclib = new vectorizeLib();
        String vname = veclib.vectorizedVersionName();
    
        System.out.println("Hello, I do " + vname);

        int n = 512;
        float[] a = new float[n];
        for (int i=0; i<n; i++) {
            a[i] = 1.0f + (float)(i & 0x0f);
        }
        
        float r1 = veclib.vectorizedInproduct(n, a, a);
        float r2 = veclib.vectorizedAverage(n, a);
        
	System.out.println("inprod = " + Float.toString(r1));
	System.out.println("average = " + Float.toString(r2));
    }
}
