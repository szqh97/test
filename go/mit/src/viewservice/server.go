package viewservice

import "net"
import "net/rpc"
import "log"
import "time"
import "sync"
import "fmt"
import "os"
import "sync/atomic"

type ViewServer struct {
	mu       sync.Mutex
	l        net.Listener
	dead     int32 // for testing
	rpccount int32 // for testing
	me       string
	// Your declarations here.

	clerkMap    map[string]time.Time
	currView    View
    backupNum   uint
}

//
// server Ping RPC handler.
//
func (vs *ViewServer) Ping(args *PingArgs, reply *PingReply) error {

	// Your code here.
    log.Println("[Ping] receive Ping ", args)
    if args.Viewnum == 24 {
        log.Println("currView is ", vs.currView)
    }
	clerkName := args.Me
	now := time.Now()
    if clerkName == "" {
        return nil
    }
    vs.clerkMap[clerkName] = now
    // first ping , set view to primary
	if vs.currView.Viewnum == 0 && len(vs.currView.Primary) == 0 && len(vs.currView.Backup) == 0 {
        vs.currView.Viewnum = args.Viewnum
		vs.currView.Primary = clerkName
		//vs.currView.Backup = ""
        reply.View = vs.currView
        return nil
	}

    // backup ping 
    if clerkName == vs.currView.Backup {
        vs.backupNum = args.Viewnum
        reply.View = vs.currView
        return nil
    }

    //primary ping 
    if clerkName == vs.currView.Primary {
        // if primary restarted, ping(0)
        if args.Viewnum < vs.currView.Viewnum {
            if vs.isviewAlive(vs.currView.Backup) {
                vs.currView.Primary = vs.currView.Backup
                vs.currView.Backup = ""
            }
            reply.View = vs.currView
            return nil
        }
        vs.currView.Viewnum = args.Viewnum 
        reply.View = vs.currView
        return nil
    }


    if vs.currView.Backup == "" {
        vs.currView.Backup = clerkName
        reply.View = vs.currView
        return nil
    }

    if !vs.isviewAlive(vs.currView.Primary) && !vs.isviewAlive(vs.currView.Backup){
        return nil
    
    }

	return nil
}

//
// server Get() RPC handler.
//
func (vs *ViewServer) Get(args *GetArgs, reply *GetReply) error {

	// Your code here.
	vs.mu.Lock()
	reply.View = vs.currView
    reply.View.Viewnum += 1
	vs.mu.Unlock()

	return nil
}

//
// tick() is called once per PingInterval; it should notice
// if servers have died or recovered, and change the view
// accordingly.
//

func (vs *ViewServer) tick() {
    log.Println("server.tick Entering...")

	// Your code here.
	primary := vs.currView.Primary
    backup := vs.currView.Backup

    if vs.isviewAlive(primary) != true {
        delete(vs.clerkMap, primary)
      //  vs.currView.Primary = ""
      // if backup's Viewnum > currView.Num then change it to primay
      // else do not change backup and primay
        if vs.isviewAlive(backup) == true && vs.currView.Viewnum >= vs.backupNum {
            vs.currView.Primary = backup
            vs.currView.Backup = ""
        }
    }

    if vs.isviewAlive(backup) == false {
        delete(vs.clerkMap, backup)
        vs.currView.Backup = ""
    }

    for clerkName, _ := range vs.clerkMap {
        if vs.currView.Primary != clerkName && vs.currView.Backup == "" {
            if vs.isviewAlive(clerkName) {
                vs.currView.Backup = clerkName
            }

        }
    }
    log.Println("[tick] server.tick Leaving ... ",vs.currView)
}

// isviewTimeOut detect whetherview is alive
// add by 97
func (vs *ViewServer) isviewAlive(view string) bool {
    now := time.Now()
    if lastPingTS, ok := vs.clerkMap[view]; ok {
        if now.Sub(lastPingTS) < PingInterval * DeadPings {
            return true
        }
    }

    // clerk is neither Primary nor backup 
    return false
}


//
// tell the server to shut itself down.
// for testing.
// please don't change these two functions.
//
func (vs *ViewServer) Kill() {
	atomic.StoreInt32(&vs.dead, 1)
	vs.l.Close()
}

//
// has this server been asked to shut down?
//
func (vs *ViewServer) isdead() bool {
	return atomic.LoadInt32(&vs.dead) != 0
}

// please don't change this function.
func (vs *ViewServer) GetRPCCount() int32 {
	return atomic.LoadInt32(&vs.rpccount)
}

func StartServer(me string) *ViewServer {
	vs := new(ViewServer)
	vs.me = me
	// Your vs.* initializations here.
	vs.clerkMap = make(map[string]time.Time)
	vs.currView.Viewnum = 0
	vs.currView.Backup = ""
	vs.currView.Backup = ""

	// tell net/rpc about our RPC server and handlers.
	rpcs := rpc.NewServer()
	rpcs.Register(vs)

	// prepare to receive connections from clients.
	// change "unix" to "tcp" to use over a network.
	os.Remove(vs.me) // only needed for "unix"
	l, e := net.Listen("unix", vs.me)
	if e != nil {
		log.Fatal("listen error: ", e)
	}
	vs.l = l

	// please don't change any of the following code,
	// or do anything to subvert it.

	// create a thread to accept RPC connections from clients.
	go func() {
		for vs.isdead() == false {
			conn, err := vs.l.Accept()
			if err == nil && vs.isdead() == false {
				atomic.AddInt32(&vs.rpccount, 1)
				go rpcs.ServeConn(conn)
			} else if err == nil {
				conn.Close()
			}
			if err != nil && vs.isdead() == false {
				fmt.Printf("ViewServer(%v) accept: %v\n", me, err.Error())
				vs.Kill()
			}
		}
	}()

	// create a thread to call tick() periodically.
	go func() {
		for vs.isdead() == false {
			vs.tick()
			time.Sleep(PingInterval)
		}
	}()

	return vs
}
