extern crate mio;
extern crate bytes;

use mio::{TryRead, TryWrite};
use mio::tcp::*;
use mio::util::Slab;
use bytes::{Buf, Take};
use std::mem;
use std::net::SocketAddr;
use std::io::Cursor;

const SERVER: mio::Token = mio::Token(0);

struct Pong {
    server: TcpListener,
    connections: Slab<Connection>,
}

impl Pong  {
    fn new(server:TcpListener) -> Pong {
        let slab = Slab::new_starting_at(mio::Token(1), 1024);
        Pong {
            server: server, 
            connections:slab,
        }
    }
}

impl mio::Handler for Pong {
    
    type TimeOut = ();
    type Message = ();
    fn ready(&mut self, event_loop: &mut mio::EventLoop<Pong>, token: mio::Token, events: mio::EventSet) {
        println!("socket is ready; token = {:?}; events = {:?}", token, envents);
        match token {
            SERVER => {
                assert!(events.is_readable());
                match self.server.accept() {
                    Ok(Some(socket)) => {
                        println!("accept a new client socket");
                        let token = self.connections
                            .insert_with(|token| Connection::new(socket, token))
                            .unwrap();

                        event_loop.register_opt(
                            &self.Connection[token].socket,
                            token,
                            mio::EventSet::readable(),
                            mio::PollOpt::edge()|mio::PollOpt::oneshot()).unwrap();
                    }
                    Ok(None) => {
                        println!("then server socket wasn't actually ready");
                    }
                    Err(e) => {
                        println!("connection error while accepting connection; err = {:?}", e);
                    }

                }
            }
            _ =>{
                self.connections[token].ready(event_loop, events);
                if self.connections[token].is_closed(){
                    let _ = self.connections.remove(token);
                }
            }
        }
        
    }
}

