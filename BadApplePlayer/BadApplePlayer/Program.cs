
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.IO;
using System.Timers;
using ClassLibrary1;


namespace BadApplePlayer
{
    
    class Program
    {
        static StreamReader reader;
        public static String[] image  = new string[3522];
        public static int num = 0;
        static void play(Object sender,ElapsedEventArgs e)
        {
            if(num>3522)return;
            Console.Clear();
            Console.Write(image[num]);
            num++;
        }

        static void Read()
        {
            ClassLibrary1.Class1 c = new Class1();
            string text = c.GetTextFromResource();
            byte[] array = Encoding.ASCII.GetBytes(text);
            MemoryStream stream = new MemoryStream(array);
            //FileStream stream = new FileStream(@"badapple.txt", FileMode.Open, FileAccess.Read);
            reader = new StreamReader(stream);
            for (int i = 0; i < 3522; i++)
            {
                String tmp = "";
                for (int j = 0; j < 30; j++)
                {
                    tmp+= reader.ReadLine()+'\n';
                }
                image[i] = tmp;
            }
            //Console.WriteLine(image[200,0]);

        }
        static void Main(string[] args)
        {

            Console.Title = "Bad Apple";
            Console.WindowHeight = 32;
            Console.WindowWidth = 80;
            Console.WriteLine("loading...");
            Read();
            Timer timer = new Timer(55);
            timer.Elapsed += new ElapsedEventHandler(play);
            timer.Enabled = true;

            Console.Read();
        }
    }
}
