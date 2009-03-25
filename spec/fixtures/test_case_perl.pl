use chilkat;

$rss = new chilkat::CkRss();

#  Download from the feed URL:
$success = $rss->DownloadRss("http://blog.chilkatsoft.com/?feed=rss2");
if ($success != 1) {
    print $rss->lastErrorText() . "\n";
    exit;
}

#  Get the 1st channel.

$rssChannel = $rss->GetChannel(0);
if ($rssChannel eq null ) {
    print "No channel found in RSS feed." . "\n";
    exit;
}