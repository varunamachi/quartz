w = new QWebChannel(qt.webChannelTransport, function (channel) {
    var qzwrapper = channel.objects.qzwrapper;
    window.qzwrapper = qzwrapper;
    qzwrapper.print("0000")
});

function qzLogJSON(any) {
    const content = JSON.stringify(any);
    if (window.qzwrapper) {
        window.qzwrapper.print(content);
    }
}


