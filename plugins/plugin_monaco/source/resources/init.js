w = new QWebChannel(qt.webChannelTransport, function (channel) {
    var qzwrapper = channel.objects.qzwrapper;
    window.qzwrapper = qzwrapper;
});
