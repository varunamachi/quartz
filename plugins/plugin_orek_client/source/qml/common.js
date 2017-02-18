function showResult(dialog, str) {
    var resultObj = JSON.parse(str)
    title: qsTr("Orek %s", resultObj.operation)
    dialog.text = resultObj.message
    dialog.icon = resultObj.error === "" ? StandardIcon.Information
                                         : StandardIcon.Critical
    dialog.visible = true
}
