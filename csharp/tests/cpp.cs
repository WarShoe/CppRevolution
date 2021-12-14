using System;
using NUnit.Framework;                  // Unit tests
using System.Runtime.InteropServices;   // for C++ binding

namespace _
{
    public sealed class CppInterface
    {
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
    public class ImpliedVolatility
    {
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
            double this_result = CppInterface.Black76(discountFactor, forward, sigma, isCallNotPut, strike, tau);
            Assert.That(expected_result, Is.EqualTo(this_result));
        }
    }
}
