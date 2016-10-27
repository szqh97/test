package uc

import "testing"

type ucTest struct {
	in, out string
}

var uctest = []ucTest{
	ucTest{"abc", "ABC"},
	ucTest{"cvo-za", "CVO-ZA"},
	ucTest{"123KK", "123KK"},
}

func TestUC(t *testing.T) {
	for _, ut := range uctest {
		uc := UpperCase(ut.in)
		if uc != ut.out {
			t.Errorf("UpperCase test errror , in %s, out: %s", ut.in, ut.out)
		}
	}
}
