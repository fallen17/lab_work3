fn print_table(table: &[(f64, f64)], title: &str) {
    println!("\n========================================");
    println!("          {}", title);
    println!("========================================");
    println!("{:>10} {:>15}", "X", "Y");
    println!("----------------------------------------");

    for (x, y) in table {
        println!("{:10.4} {:15.4}", x, y);
    }
    
    println!("========================================\n");
}

fn func_circle(tab_xy: &mut Vec<(f64, f64)>) {
    let r: f64 = 2.0;
    let step: f64 = 0.5;

    let mut x: f64 = -10.0;
    while x <= -6.0 + 0.001 {
        let y = -2.0 + (r.powi(2) - f64::powi(x + 8.0, 2)).sqrt();

        if !y.is_nan() {
            tab_xy.push((x, y));
        }
        x += step;
    }
}

fn func_line(tab_xy: &mut Vec<(f64, f64)>) {
    let k: f64 = 0.6;
    let b: f64 = 1.6;
    
    let mut x: f64 = -6.0;
    while x <= -1.0 + 0.001 {
        let y = k * x + b;
        tab_xy.push((x, y));
        x += 1.0;
    }
}

fn func_const(tab_xy: &mut Vec<(f64, f64)>) {
    let step: f64 = 0.5;

    let mut x: f64 = -1.0;
    while x <= 2.0 + 0.001 {
        let y = 0.0;
        tab_xy.push((x, y));
        x += step;
    }
}

fn func_parabola(tab_xy: &mut Vec<(f64, f64)>) {
    let step: f64 = 0.2;

    let mut x: f64 = 2.0;
    while x <= 3.0 + 0.001 {
        let y = f64::powi(x - 2.0, 2);
        tab_xy.push((x, y));
        x += step;
    }
}

fn main() {
    let mut tab_circle: Vec<(f64, f64)> = Vec::new();
    let mut tab_line: Vec<(f64, f64)> = Vec::new();
    let mut tab_const: Vec<(f64, f64)> = Vec::new();
    let mut tab_parabola: Vec<(f64, f64)> = Vec::new();

    func_circle(&mut tab_circle);
    func_line(&mut tab_line);
    func_const(&mut tab_const);
    func_parabola(&mut tab_parabola);

    print_table(&tab_circle, "Circle (upper half)");
    print_table(&tab_line, "Line");
    print_table(&tab_const, "Constant");
    print_table(&tab_parabola, "Parabola");
}