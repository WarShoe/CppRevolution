using System;
using NUnit.Framework;                  // Unit tests
using System.Runtime.InteropServices;   // for C++ binding

namespace _
{
    public sealed class CppInterface
    {
        // [DllImport("/Users/zvyagin/Projects/ProjectZ/build/csharp/libnumerics_csharp.dylib")]
        [DllImport("libnumerics_csharp")]
        public static extern double Black76 (
            double discountFactor,
            double forward,
            double sigma,
            bool isCallNotPut,
            double strike,
            double tau
        );
    }

    [TestFixture]
    public class TestCppInterface
    {
        [Test()]
        public static void f()
        {
            try
            {
                CppInterface.Black76(1, 100, 1, true, 120, 5);

            }
            catch (DllNotFoundException e)
            {
                Assert.Pass(e.ToString());
            }
        }
    }
    
    [TestFixture]
    public class ImpliedVolatility
    {
        // C++ binding
        //[DllImport("/Users/zvyagin/Projects/ProjectZ/build/csharp/libnumerics_csharp.dylib")]

        // keeping the same arguments to what is found in the other source file
        [DllImport("libnumerics_csharp")]
        public static extern double Black76 (
            double discountFactor,
            double forward,
            double sigma,
            bool isCallNotPut,
            double strike,
            double tau
        );

        [TestCase(71.18312286330693,1,100,1,true ,120,5)]
        [TestCase(91.18312286330693,1,100,1,false,120,5)]
        public static void Test_Black76 (
            double expected_result,
            double discountFactor,
            double forward,
            double sigma,
            bool isCallNotPut,
            double strike,
            double tau
        ){
            try
            {
                double this_result = Black76(discountFactor, forward, sigma, isCallNotPut, strike, tau);
                Assert.That(expected_result, Is.EqualTo(this_result));
            }
            catch (DllNotFoundException e)
            {
                Assert.Fail(e.ToString());
            }
        }
    }
}
