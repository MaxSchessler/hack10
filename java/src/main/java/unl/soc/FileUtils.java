package unl.soc;
import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.FileWriter;
import java.io.IOException;
import java.util.ArrayList;
import java.util.List;

/**
 * 
 * Author: Max Schessler
 * Date: 2024-11-10
 * 
 * The FileUtils class provides utility methods for reading the contents of files.
 * It includes methods to read the entire content of a file as a string and to read
 * all lines of a file into a list of strings.
*/
public class FileUtils {

    /**
     * Reads the contents of a file specified by the given file path and returns it
     * as a string.
     *
     * @param filePath the path to the file to be read
     * @return the contents of the file as a string, or null if the file does not
     *         exist or an error occurs during reading
     */
    public static String getFileContents(String filePath) {

        File file = new File(filePath);

        try (BufferedReader reader = new BufferedReader(new FileReader((file)))) {
            StringBuilder sb = new StringBuilder();

            char c;

            while (true) {
                c = (char) reader.read();
                // check if char is null
                if (c == (char) -1) {
                    break;
                }
                sb.append(c);
            }

            return sb.toString();

        } catch (FileNotFoundException e) {
            e.printStackTrace();
            System.err.printf("%s does not exist.\n", filePath);
            System.exit(1);
        } catch (IOException e) {
            e.printStackTrace();
            System.err.printf("%s error occured when reading %s", e.getMessage(), filePath);
            System.exit(1);
        }

        return null;
    }

    /**
     * Reads all lines from a file specified by the given file path.
     *
     * @param filePath the path to the file to be read
     * @return a list of strings, each representing a line in the file, or null if
     *         an error occurs
     */
    public static List<String> getFileLines(String filePath) {

        try (BufferedReader reader = new BufferedReader(new FileReader(new File(filePath)))) {

            List<String> lines = new ArrayList<String>();
            String line;
            while (true) {
                line = reader.readLine();
                if (line == null) {
                    break;
                }

                lines.add(line);
            }

            return lines;

        } catch (FileNotFoundException e) {
            e.printStackTrace();
            System.err.printf("%s does not exist.\n", filePath);
            return null;
        } catch (IOException e) {
            e.printStackTrace();
            System.err.printf("%s error occured when reading %s\n", e.getMessage(), filePath);
            return null;
        }
    }

    /**
     * Writes a list of characters to a specified file.
     *
     * @param filePath the path of the file to write to
     * @param chars the list of characters to write to the file
     */
    public static void writeArrayOfCharsToFile(String filePath, List<Character> chars) {
        try (BufferedWriter writer = new BufferedWriter(new FileWriter(new File(filePath)))) {
            for (char c : chars) {
                writer.write(c);
            }
        } catch (IOException e) {
            e.printStackTrace();
            System.err.printf("%s error occued when writing to %s\n", e.getMessage(), filePath );
        }
    }
}
