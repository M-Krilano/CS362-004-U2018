import junit.framework.TestCase;
import java.util.Random;
//You can use this as a skeleton for your 3 different test approach
//It is an optional to use this file, you can generate your own test file(s) to test the target function!
// Again, it is up to you to use this file or not!





public class UrlValidatorTest extends TestCase {
	// 4 true test scheme cases
	String[] trueUrlScheme = {
			"http://",
            "ftp://",
            "h3t://",
            ""
            };
	// 5 false test scheme cases
	String[] falseUrlScheme = {
            "3ht://",
            "http:/",
            "http:",
            "http/",
            "://"
            };
	// 6 true test authority cases
	String[] trueUrlAuthority = {
			"www.google.com",
            "go.com",
            "go.au",
            "0.0.0.0",
            "255.255.255.255",
            "255.com"
            };
	// 12 false test authority cases
	String[] falseUrlAuthority = {
            "256.256.256.256",
            "1.2.3.4.5",
            "1.2.3.4.",
            "1.2.3",
            ".1.2.3.4",
            "go.a",
            "go.a1a", 
            "go.1aa", 
            "aaa.", 
            ".aaa",
            "aaa",
            ""
            };
	// 4 true port cases
	String[] trueUrlPort = {
		":80",
        ":65535",
        ":0",
        ""
        };
	// 3 false port cases
	String[] falseUrlPort = {
		":-1",
        ":65636",
        ":65a"
        };
	// 8 true path cases
	String[] truePath = {
		"/test1",
        "/t123",
        "/$23",
        "/test1/",
        "",
        "/test1/file",
        "/t123/file",
        "/$23/file"
        };
	// 6 false path cases
	String[] falsePath = {
      "/..",
      "/../",
      "/..//file",
      "/test1//file",
      "/../file",
      "/#/file"
      };
	// 3 true query cases
	String[] trueUrlQuery = {
		"?action=view",
        "?action=edit&mode=up",
        ""
        };
	
	
   public UrlValidatorTest(String testName) {
      super(testName);
   }

   public static void main(String[] argv) {
	   UrlValidatorTest urlTest = new UrlValidatorTest("Url Validator Test");
	   
	   urlTest.testManualTest();	   
//	   urlTest.testYourFirstPartition();
//	   urlTest.testYourSecondPartition();
//	   urlTest.testIsValid();
   }
   
   public void testManualTest()
   {
	   //You can use this function to implement your manual testing
	   //You can use this function to implement your manual testing
	   int size = 5;
	   boolean result = true;
	   String errorType, errorMsg = "";
	   String goodUrls[] = new String[size];
	   String badUrls[] = new String[size];	 	 
	   
	   UrlValidator urlVal = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);
	   
	   // Manually create some valid URLs.
	   goodUrls[0] = "http://www.google.com/test1";
	   goodUrls[1] = "http://www.valid.com:50/somePath?action=view";
	   goodUrls[2] = "http://www.yahoo.com/somePath?action=update";
	   goodUrls[3] = "http://www.myserver.net";
	   goodUrls[4] = "http://www.osu.cs.com/somePath?action=update";
	   
	   // The following tests expect the URLs to be valid, isValid() should return true.
	   errorType = "\n\tExpected valid, but received invalid - ";
	   for (int i = 0; i < size; i++) {
		   if (urlVal.isValid(goodUrls[i]) == false) {	// Since it returns false, this case is a bug.			   
			   result = false;
			   errorMsg += errorType + goodUrls[i];
		   }
	   }
	   
	   // Manually create some invalid URLs.
	   badUrls[0] = "http://www.go    ogle.com";
	   badUrls[1] = "http://www.att.net:50a/somePath?action=view";	   
	   badUrls[2] = "http://yahoo.com/../?action=";
	   badUrls[3] = "http://.microsoft";
	   badUrls[4] = "http://www.osu.cs.com:-1";
	   
	   // The following tests expect the URLs to be invalid, isValid() should return false. 
	   errorType = "\n\tExpected invalid, but received valid - ";
	   for (int i = 0; i < size; i++) {
		   if (urlVal.isValid(badUrls[i]) == true) {	// Since it returns true, this case is a bug.			   
			   result = false;
			   errorMsg += errorType + badUrls[i];
		   }
	   }
	   	   
	   System.out.print("Manual Testing - The following errors are found:");
	   if (result == false) 		   
		   System.out.println(errorMsg);
	   else
		   System.out.println("\n\tNo bugs found.");
	   
	   // assertTrue(errorMsg, result);    <<-- Uncomment if run unit tests in Eclipse IDE
	   
   }
   
   
   public void testYourFirstPartition()
   {
	 //You can use this function to implement your First Partition testing	   

   }
   
   public void testYourSecondPartition(){
	   //You can use this function to implement your Second Partition testing	   

   }
   //You need to create more test cases for your Partitions if you need to 
   
   public void testIsValid()
   {
	   System.out.println("Unit Testing for isValid function\n");
	   // Generate random seed
	   Random randomnum = new Random();

	   //empty true and false strings
	   String TRUE_TEST_URL = "";
	   String FALSE_TEST_URL = "";
	   
	   // true and false urlValidators
	   UrlValidator TRUE_URL_VALIDATOR;
	   UrlValidator FALSE_URL_VALIDATOR;
	   
	   // Expected trueCount and falseCount
	   int expectedTrueCount = 1000;
	   int expectedFalseCount = 1000;
	   
	   // Actual trueCount and falseCount
	   int actualTrueCount = 0;
	   int actualFalseCount = 0;
	
	   //Loop 1000 times
	   for (int i = 0; i < 1000; i++)
	   {		   
		   // random true URL
		   TRUE_TEST_URL = trueUrlScheme[randomnum.nextInt(4)] + trueUrlAuthority[randomnum.nextInt(6)] +
				   trueUrlPort[randomnum.nextInt(4)] + truePath[randomnum.nextInt(8)] + trueUrlQuery[randomnum.nextInt(3)];
		   // random false URL
		   FALSE_TEST_URL = falseUrlScheme[randomnum.nextInt(5)] + falseUrlAuthority[randomnum.nextInt(12)] +
				   falseUrlPort[randomnum.nextInt(3)] + falsePath[randomnum.nextInt(6)];

		   //verify the true URLs
		   TRUE_URL_VALIDATOR = new UrlValidator(null, null, UrlValidator.ALLOW_LOCAL_URLS);
		   if( TRUE_URL_VALIDATOR.isValid(TRUE_TEST_URL) ) {
			   ++actualTrueCount;
		   };
		   //verify the false URLs
		   FALSE_URL_VALIDATOR = new UrlValidator(null, null, UrlValidator.ALLOW_LOCAL_URLS);
		   if( FALSE_URL_VALIDATOR.isValid(FALSE_TEST_URL) ) {
			   ++actualFalseCount;
		   };
		   // reset TEST URLs
		   TRUE_TEST_URL = "";
		   FALSE_TEST_URL = "";
	   }
	   // compare expected to actual
	   System.out.println("");
	   System.out.println("UNIT TEST: expected true urls\n");
	   assertTrue(actualTrueCount == expectedTrueCount);
	   
	   // compare expected to actual
	   System.out.println("");
	   System.out.println("UNIT TEST: expected false urls\n");
	   assertTrue(actualFalseCount == expectedFalseCount);
   }
}
