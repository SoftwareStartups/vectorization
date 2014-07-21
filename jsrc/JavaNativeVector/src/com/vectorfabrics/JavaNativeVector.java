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
        vectorizeLib top = new vectorizeLib();
        String vname = top.vectorizedVersionName();
        System.out.println("Hello me");
        System.out.println(vname);

    }
    
}
