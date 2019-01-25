w = new QWebChannel(qt.webChannelTransport, function (channel) {
    var qzwrapper = channel.objects.qzwrapper;
    window.qzwrapper = qzwrapper;
    console.log("0000")
    qzwrapper.contentSet.connect(function(content) {
        console.log("1111")
        editor.setValue(content);
    })
});

