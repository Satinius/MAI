using System;
using Windows.UI.Xaml.Controls;
using Windows.UI.Xaml.Input;
using Windows.UI.Xaml.Media;
using Windows.UI.Xaml.Shapes;

namespace CG_lab1
{
     public sealed partial class MainPage : Page
    {
        public MainPage()
        {
            this.InitializeComponent();
        }

        private void drawCurve(object sender, TappedRoutedEventArgs e)
        {
            var a = float.Parse(input_a.Text, System.Globalization.CultureInfo.InvariantCulture);
            var A = float.Parse(input_A.Text, System.Globalization.CultureInfo.InvariantCulture);
            var B = float.Parse(input_B.Text, System.Globalization.CultureInfo.InvariantCulture);
            var curve = new Polyline
            {
                Stroke = new SolidColorBrush(Windows.UI.Colors.Black),
                StrokeThickness = 2
            };
            var points = new PointCollection();
            var point_count = 100;
            var delta = (B - A) / point_count;
            var scaling = 25;
            for (var phi = A; phi <= B; phi += delta)
            {
                var rho = Math.Cos(2 * phi) / Math.Cos(phi);
                var x = (rho * Math.Cos(phi) * scaling + Graphic.Width / 2);
                var y = (rho * Math.Sin(phi) * scaling + Graphic.Height / 2);
                System.Diagnostics.Debug.WriteLine($"({x},{y}), ({phi}, {rho})");
                points.Add(new Windows.Foundation.Point(x, y));
            }
            curve.Points = points;
            Graphic.Children.Clear();
            Graphic.Children.Add(new Line { Stroke = new SolidColorBrush(Windows.UI.Colors.Black), StrokeThickness = 1, X2 = Graphic.Width, Y2 = Graphic.Height / 2 , Y1 = Graphic.Height / 2});
            Graphic.Children.Add(new Line { Stroke = new SolidColorBrush(Windows.UI.Colors.Black), StrokeThickness = 1, Y2 = Graphic.Width, X1 = Graphic.Width / 2, X2 = Graphic.Width / 2 });

            Graphic.Children.Add(curve);
        }
    }
}
