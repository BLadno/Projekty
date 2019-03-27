package jUnit;

import static org.junit.Assert.*;

import org.junit.Test;

public class UnitTest1 {

	@Test
	public void testAddTrue() {
		Test1 test = new Test1();
		int result = test.add(2, 5);
		assertEquals(7,result);
		//fail("Not yet implemented");
	}
	@Test
	public void testAddFalse() {
		Test1 test = new Test1();
		int result = test.add(2, 5);
		assertTrue(result != 9);
		//fail("Not yet implemented");
	}

}
