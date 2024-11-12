package unl.soc;
/**
 * Author: Max Schessler
 * Date: 2024-11-10
 * 
 * The ProteinTranslator class provides a mapping from DNA/RNA codons to their corresponding
 * amino acids. The mapping is stored in a static final HashMap called proteinMap.
 * 
 */
//package unl.soc;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

public class ProteinTranslator {

  /**
	 * Trigram DNA to protein map
	 */
	public static final Map<String, Character> proteinMap = new HashMap<>();

	static {

		proteinMap.put("AAA", 'K');
		proteinMap.put("AAC", 'N');
		proteinMap.put("AAG", 'K');
		proteinMap.put("AAU", 'N');
		proteinMap.put("ACA", 'T');
		proteinMap.put("ACC", 'T');
		proteinMap.put("ACG", 'T');
		proteinMap.put("ACU", 'T');
		proteinMap.put("AGA", 'R');
		proteinMap.put("AGC", 'S');
		proteinMap.put("AGG", 'R');
		proteinMap.put("AGU", 'S');
		proteinMap.put("AUA", 'I');
		proteinMap.put("AUC", 'I');
		proteinMap.put("AUG", 'M');
		proteinMap.put("AUU", 'I');
		proteinMap.put("CAA", 'Q');
		proteinMap.put("CAC", 'H');
		proteinMap.put("CAG", 'Q');
		proteinMap.put("CAU", 'H');
		proteinMap.put("CCA", 'P');
		proteinMap.put("CCC", 'P');
		proteinMap.put("CCG", 'P');
		proteinMap.put("CCU", 'P');
		proteinMap.put("CGA", 'R');
		proteinMap.put("CGC", 'R');
		proteinMap.put("CGG", 'R');
		proteinMap.put("CGU", 'R');
		proteinMap.put("CUA", 'L');
		proteinMap.put("CUC", 'L');
		proteinMap.put("CUG", 'L');
		proteinMap.put("CUU", 'L');
		proteinMap.put("GAA", 'E');
		proteinMap.put("GAC", 'D');
		proteinMap.put("GAG", 'E');
		proteinMap.put("GAU", 'D');
		proteinMap.put("GCA", 'A');
		proteinMap.put("GCC", 'A');
		proteinMap.put("GCG", 'A');
		proteinMap.put("GCU", 'A');
		proteinMap.put("GGA", 'G');
		proteinMap.put("GGC", 'G');
		proteinMap.put("GGG", 'G');
		proteinMap.put("GGU", 'G');
		proteinMap.put("GUA", 'V');
		proteinMap.put("GUC", 'V');
		proteinMap.put("GUG", 'V');
		proteinMap.put("GUU", 'V');
		proteinMap.put("UAA", 'x');
		proteinMap.put("UAC", 'Y');
		proteinMap.put("UAG", 'x');
		proteinMap.put("UAU", 'Y');
		proteinMap.put("UCA", 'S');
		proteinMap.put("UCC", 'S');
		proteinMap.put("UCG", 'S');
		proteinMap.put("UCU", 'S');
		proteinMap.put("UGA", 'x');
		proteinMap.put("UGC", 'C');
		proteinMap.put("UGG", 'W');
		proteinMap.put("UGU", 'C');
		proteinMap.put("UUA", 'L');
		proteinMap.put("UUC", 'F');
		proteinMap.put("UUG", 'L');
		proteinMap.put("UUU", 'F');
	}

	public static void main(String args[]) {
		
        String inputFile = args[0];
        String outputFile = args[1];
        // String inputFile = "data/dnaSample002.txt";
        // String outputFile = "data/output/protein.txt";

        // Read contents of input file
        String contents = FileUtils.getFileContents(inputFile);
        // clean contents of file and split into list of 3 character long strings
        contents = replaceChar(contents, 'T', 'U');
        contents = removeChar(contents, '\n');
        contents = removeChar(contents, ' ');
        List<String> rnaSequence = lengthSplit(contents, 3);
        List<Character> proteins = convertToProteins(rnaSequence);
        FileUtils.writeArrayOfCharsToFile(outputFile, proteins);
	}

    /**
     * Converts a list of RNA sequences to a list of corresponding proteins.
     *
     * @param rnaSequence a list of RNA sequences represented as strings
     * @return a list of proteins represented as characters
     */
    public static List<Character> convertToProteins(List<String> rnaSequence) {
        List<Character> proteins = new ArrayList<Character>();
        char protein; 
        for (String rna : rnaSequence) {
            protein = proteinMap.get(rna);
            if (protein == 'x') {
                break;
            }

            proteins.add(protein);
        }
        return proteins;
    }

    /**
     * Replaces all occurrences of a specified character in the given string with a new character.
     *
     * @param s       the string in which to replace characters
     * @param oldChar the character to be replaced
     * @param newChar the character to replace with
     * @return a new string with the specified character replaced
     * @throws IllegalArgumentException if the input string is null
     */
    public static String replaceChar(String s, char oldChar, char newChar) {
        if (s == null) {
            throw new IllegalArgumentException("String is null");
        }
        return s.replace(oldChar, newChar);
    }

    /**
     * Removes all occurrences of the specified character from the given string.
     *
     * @param s the string from which to remove the character
     * @param c the character to be removed
     * @return a new string with the specified character removed
     * @throws IllegalArgumentException if the input string is null
     */
    public static String removeChar(String s, char c) {
        if (s == null) {
            throw new IllegalArgumentException("String is null");
        }
        StringBuilder sb = new StringBuilder(s);
        for (int i = 0; i < sb.length(); i++) {
            if (sb.charAt(i) == c) {
                sb.deleteCharAt(i);
                i --; // this will decrement the index to check the new value at i
            }
        }
        return sb.toString();
    }

    /**
     * Splits the given string into substrings of the specified length.
     *
     * @param s the string to be split
     * @param n the length of each substring
     * @return a list of substrings of the specified length
     * @throws IllegalArgumentException if the input string is null or n is less than 1
     */
    public static List<String> lengthSplit(String s, int n) {
        if (s == null || n < 1) {
            throw new IllegalArgumentException("String is null or n is less than 1");
        }

        int strLen = s.length();
        List<String> result = new ArrayList<>();

        for (int i = 0; i < strLen; i += n) {
            int endIndex = Math.min(i + n, strLen);
            result.add(s.substring(i, endIndex));
        }

        return result;
    }

}