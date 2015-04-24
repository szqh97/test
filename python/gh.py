from ghost import Ghost

url = "http://news.ycombinator.com/"
# We enable the cache and set the maximun size to 10 MB
# We don't want to load images and load css or js files
gh = Ghost( download_images=False)

# wait_onload_event will tell to Ghost to leave the open method
# when the On Ready event on the web page has been fired
page, resources = gh.open(url)

# We retrive the links from the web page
links = gh.evaluate("""
    function byId(id) {
      return document.getElementById(id);
    }

    function vote(node) {
      var v = node.id.split(/_/);   // {'up', '123'}
      var item = v[1];

      // hide arrows
      byId('up_'   + item).style.visibility = 'hidden';
      byId('down_' + item).style.visibility = 'hidden';

      // ping server
      var ping = new Image();
      ping.src = node.href;

      return false; // cancel browser nav
                        """)
# Print the links
print links
#for l in links[0]:
#    print l
