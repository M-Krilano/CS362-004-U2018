import junit.framework.TestCase;
import java.util.Random;

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
   
   public void testManualTest()
   {
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
   
   /*
    * For the following input partitioning tests, the URL is broken into
    * four parts: Scheme, Authority, Path, Query.
    */
   
   public void testSchemePartition() {
	   UrlValidator u = new UrlValidator(null, null, 0);
	   
	   assertTrue(u.isValid("http://www.google.com/gmail"));
	   assertTrue(u.isValid("https://www.google.com/gmail"));
	   assertTrue(u.isValid("ftp://www.google.com/gmail"));
       assertFalse(u.isValid("http:/www.google.com/gmail"));
	   assertFalse(u.isValid("f1p://www.google.com/gmail"));
       assertFalse(u.isValid("www.google.com/gmail"));
	   
	   u = new UrlValidator(new String [] { "http" }, null, 0);
	   
	   assertTrue(u.isValid("http://www.google.com/gmail"));
	   assertFalse(u.isValid("https://www.google.com/gmail"));
	   assertFalse(u.isValid("ftp://www.google.com/gmail"));
	   assertFalse(u.isValid("http:/www.google.com/gmail"));
	   assertFalse(u.isValid("f1p://www.google.com/gmail"));
	   assertFalse(u.isValid("www.google.com/gmail"));
	   
	   u = new UrlValidator(new String [] { "http" }, null, UrlValidator.ALLOW_ALL_SCHEMES);

	   assertTrue(u.isValid("http://www.google.com/gmail"));
	   assertTrue(u.isValid("https://www.google.com/gmail"));
	   assertTrue(u.isValid("ftp://www.google.com/gmail"));
	   assertFalse(u.isValid("http:/www.google.com/gmail"));
	   assertTrue(u.isValid("f1p://www.google.com/gmail"));
	   assertFalse(u.isValid("www.google.com/gmail"));
   }
   
   public void testAuthorityPartition() {
	   UrlValidator u = new UrlValidator(null, null, 0);
	   
	   assertTrue(u.isValid("http://www.google.com/gmail"));
	   assertTrue(u.isValid("http://WWW.GOOGLE.COM/gmail"));
	   assertTrue(u.isValid("http://www.g00gl3.com/gmail"));
	   assertFalse(u.isValid("http://www.goog%e.com/gmail"));
	   assertTrue(u.isValid("http://255.255.255.255/gmail"));
	   assertFalse(u.isValid("http://255.255.255.-1/gmail"));
	   assertFalse(u.isValid("http://255.255.255.256/gmail"));
	   assertFalse(u.isValid("http://255.255.255/gmail"));
   }
   
   public void testPathPartition() {   
	   UrlValidator u = new UrlValidator(null, null, 0);
	   
	   assertTrue(u.isValid("http://www.google.com/gmail"));
	   assertTrue(u.isValid("http://www.google.com/gmai1"));
	   assertFalse(u.isValid("http://www.google.com/.."));
	   assertFalse(u.isValid("http://www.google.com//gmail"));
   }
   
   public void testQueryPartition() {
	   
	   UrlValidator u = new UrlValidator(null, null, 0);
	   
	   assertTrue(u.isValid("http://www.google.com/gmail"));
	   assertTrue(u.isValid("http://www.google.com/gmail?i=1"));
	   assertTrue(u.isValid("http://www.google.com/gmail?this=start"));   
   }
   
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
	
	   // Loop 1000 times
	   for (int i = 0; i < 1000; i++)
	   {		   
		   // random true URL
		   TRUE_TEST_URL = trueUrlScheme[randomnum.nextInt(4)] + trueUrlAuthority[randomnum.nextInt(6)] +
				   trueUrlPort[randomnum.nextInt(4)] + truePath[randomnum.nextInt(8)] + trueUrlQuery[randomnum.nextInt(3)];
		   // random false URL
		   FALSE_TEST_URL = falseUrlScheme[randomnum.nextInt(5)] + falseUrlAuthority[randomnum.nextInt(12)] +
				   falseUrlPort[randomnum.nextInt(3)] + falsePath[randomnum.nextInt(6)];

		   // verify the true URLs
		   TRUE_URL_VALIDATOR = new UrlValidator(null, null, UrlValidator.ALLOW_LOCAL_URLS);
		   if( TRUE_URL_VALIDATOR.isValid(TRUE_TEST_URL) ) {
			   ++actualTrueCount;
		   };
		   // verify the false URLs
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