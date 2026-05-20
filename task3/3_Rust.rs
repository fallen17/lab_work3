use std::io;

fn gcd(mut a: i64, mut b: i64) -> i64 {
    while b != 0 {
        a %= b;
        std::mem::swap(&mut a, &mut b);
    }
    a
}

fn power(base: i64, exp: u32) -> i64 {
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

    let mut c: Vec<i64> = vec![0; (a + 1) as usize];
    c[1] = 1;

    for k in 1..a {
        let mut next_c = vec![0i64; (a + 1) as usize];
        for i in 1..=k as usize {
            next_c[i] += (i as i64) * c[i];
            if i + 1 <= a as usize {
                next_c[i + 1] += (k as i64 + 1 - i as i64) * c[i];
            }
        }
        c = next_c;
    }

    let mut numerator: i64 = 0;
    for i in 1..=a as usize {
        numerator += c[i] * power(b as i64, (a - i as i32) as u32);
    }
    numerator *= b as i64;

    let denominator = power((b - 1) as i64, (a + 1) as u32);

    let common = gcd(numerator, denominator);
    let final_num = numerator / common;
    let final_den = denominator / common;

    println!("{}/{}", final_num, final_den);
}