use std::io;

fn gcd(mut a: i128, mut b: i128) -> i128 {
    while b != 0 {
        a %= b;
        std::mem::swap(&mut a, &mut b);
    }
    a
}

fn power(base: i128, exp: u32) -> i128 {
    if exp == 0 { return 1; }
    base.pow(exp)
}

fn main() {
    let mut input = String::new();
    
    if io::stdin().read_line(&mut input).is_err() {
        return;
    }
    
    let parts: Vec<i32> = input
        .split_whitespace()
        .filter_map(|s| s.parse().ok())
        .collect();

    if parts.len() < 2 {
        return;
    }

    let a = parts[0];
    let b = parts[1];

    if b == 1 {
        println!("infinity");
        return;
    }

    let mut c: Vec<i128> = vec![0; (a + 1) as usize];
    c[1] = 1;

    for k in 1..a {
        let mut next_c = vec![0i128; (a + 1) as usize];
        for i in 1..=k as usize {
            next_c[i] += (i as i128) * c[i];
            if i + 1 <= a as usize {
                next_c[i + 1] += (k as i128 + 1 - i as i128) * c[i];
            }
        }
        c = next_c;
    }

    let mut numerator: i128 = 0;
    for i in 1..=a as usize {
        numerator += c[i] * power(b as i128, (a - i as i32) as u32);
    }
    numerator *= b as i128;

    let denominator = power((b - 1) as i128, (a + 1) as u32);

    let common = gcd(numerator, denominator);
    let final_num = numerator / common;
    let final_den = denominator / common;

    println!("{}/{}", final_num, final_den);
}