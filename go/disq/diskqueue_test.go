package nsqd
import (
    "log"
    "time"
    "testing"
    "os"
    "strconv"

	"github.com/bmizerany/assert"
)

func Testdiskqueue(t *testing.T) {

	dqName := "test_disk_queue" + strconv.Itoa(int(time.Now().Unix()))
    log.Println("dqName is ", dqName)
    cwd, _ := os.Getwd()
	dq := newDiskQueue(dqName, cwd, 1024, 2500, 2*time.Second)
    log.Println("depth: ", dq.Depth())

	msg := []byte("test test test")
	err := dq.Put(msg)
    log.Println("depth: ", dq.Depth())
   if err != nil{
       log.Println("err is : ", err)
   }
	msgOut := <-dq.ReadChan()
    log.Println("msgout is : ", msgOut)
    log.Println("depth: ", dq.Depth())
}

func TestdiskQueueRoll(t *testing.T) {

	dqName := "test_disk_queue_roll" + strconv.Itoa(int(time.Now().Unix()))
    cwd, _ := os.Getwd()
	dq := newDiskQueue(dqName, cwd, 1024, 2500, 2*time.Second)
    log.Println("depth of dq: ", dq.Depth())

	msg := []byte("aaaaaaaaaa")
	for i := 0; i < 100; i++ {
		err := dq.Put(msg)
        if err != nil {
            log.Println("err is: ", err.Error())
        }
	}
    //log.Println("the writeFileNum: ", dq.(*diskQueue).WriteFileNum)
    //log.Println("the diskQueue: ", dq.(*diskQueue).WritePos)

    //assert.Equal(t, dq.(*diskQueue).writeFileNum, int64(1))
	//assert.Equal(t, dq.(*diskQueue).writePos, int64(28))
}
func assertFileNotExist(t *testing.T, fn string) {
	f, err := os.OpenFile(fn, os.O_RDONLY, 0600)
	assert.Equal(t, f, (*os.File)(nil))
	assert.Equal(t, os.IsNotExist(err), true)
}

func TestDiskQueueEmpty(t *testing.T) {
	dqName := "test_disk_queue_empty" + strconv.Itoa(int(time.Now().Unix()))
    cwd, _ := os.Getwd()
	dq := newDiskQueue(dqName, cwd, 100, 2500, 2*time.Second)

	msg := []byte("aaaaaaaaaa")

	for i := 0; i < 100; i++ {
		err := dq.Put(msg)
		assert.Equal(t, err, nil)
		assert.Equal(t, dq.Depth(), int64(i+1))
	}

	for i := 0; i < 3; i++ {
		<-dq.ReadChan()
	}

	for {
		if dq.Depth() == 97 {
            log.Println("xxxxxxxxxxxxxx")
			break
		}
		time.Sleep(50 * time.Millisecond)
	}
	assert.Equal(t, dq.Depth(), int64(97))

	numFiles := dq.(*diskQueue).writeFileNum
	dq.Empty()
    log.Println("numFile :" , numFiles)

	assertFileNotExist(t, dq.(*diskQueue).metaDataFileName())
	for i := int64(0); i <= numFiles; i++ {
		assertFileNotExist(t, dq.(*diskQueue).fileName(i))
	}
	assert.Equal(t, dq.Depth(), int64(0))
	assert.Equal(t, dq.(*diskQueue).readFileNum, dq.(*diskQueue).writeFileNum)
	assert.Equal(t, dq.(*diskQueue).readPos, dq.(*diskQueue).writePos)
	assert.Equal(t, dq.(*diskQueue).nextReadPos, dq.(*diskQueue).readPos)
	assert.Equal(t, dq.(*diskQueue).nextReadFileNum, dq.(*diskQueue).readFileNum)

	for i := 0; i < 100; i++ {
		err := dq.Put(msg)
		assert.Equal(t, err, nil)
		assert.Equal(t, dq.Depth(), int64(i+1))
	}

	for i := 0; i < 100; i++ {
		<-dq.ReadChan()
	}

	for {
		if dq.Depth() == 0 {
			break
		}
		time.Sleep(50 * time.Millisecond)
	}

	assert.Equal(t, dq.Depth(), int64(0))
	assert.Equal(t, dq.(*diskQueue).readFileNum, dq.(*diskQueue).writeFileNum)
	assert.Equal(t, dq.(*diskQueue).readPos, dq.(*diskQueue).writePos)
	assert.Equal(t, dq.(*diskQueue).nextReadPos, dq.(*diskQueue).readPos)
}
