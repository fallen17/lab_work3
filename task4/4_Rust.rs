use std::io;
use std::cmp;

fn game(chain: &[i64], n: usize, m: usize) {
    let mut last_k: i32 = 0;
    let mut index: usize = 0;

    let mut prefix = vec![0i64; n + 1];
    for i in 0..n {
        prefix[i + 1] = prefix[i] + chain[i];
    }

    let mut score_pasha = 0i64;
    let mut score_vik = 0i64;
    let mut pasha_turn = true;

    while index < n {
        let max_len = cmp::min(m, n - index);
        let mut best_k: i32 = -1;
        let mut best_sum = i64::MIN; // Аналог -1e18

        for k in 1..=max_len {
            if k as i32 == last_k {
                continue;
            }

            let sum = prefix[index + k] - prefix[index];
            
            if sum > best_sum || (sum == best_sum && (best_k == -1 || (k as i32) < best_k)) {
                best_sum = sum;
                best_k = k as i32;
            }
        }

        if best_k == -1 {
            break;
        }

        if pasha_turn {
            score_pasha += best_sum;
        } else {
            score_vik += best_sum;
        }

        last_k = best_k;
        index += best_k as usize;
        pasha_turn = !pasha_turn;
    }

    if score_pasha > score_vik {
        println!("1");
    } else {
        println!("0");
    }
}

fn main() {
    let mut input = String::new();
    
    println!("Type in number n");
    io::stdin().read_line(&mut input).unwrap();
    let n: usize = input.trim().parse().unwrap();
    input.clear();

    println!("Type in number m");
    io::stdin().read_line(&mut input).unwrap();
    let m: usize = input.trim().parse().unwrap();
    input.clear();

    println!("Type in {} numbers", n);
    
    let mut chain_n = Vec::with_capacity(n);
    while chain_n.len() < n {
        let mut line = String::new();
        io::stdin().read_line(&mut line).unwrap();
        for word in line.split_whitespace() {
            if let Ok(num) = word.parse::<i64>() {
                if chain_n.len() < n {
                    chain_n.push(num);
                }
            }
        }
    }

    game(&chain_n, n, m);
}