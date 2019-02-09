function qzLogJSON(any) {
    const content = JSON.stringify(any);
    if (window.qzwrapper) {
        window.qzwrapper.info(cnt);
    }
}


function getContentID() {
    if (window.editor) {
        return editor.getModel().getAlternativeVersionId();
    }
    return '';
}

function setContent(content) {
    window.editor.setValue(content);
    window.contentID = getContentID();
}

var editor = monaco.editor.create(
    document.getElementById('container'), {
        automaticLayout: true,
        value: '',
});

editor.addAction({
    id: 'qzp.webtech.save',
    label: 'Save',
    keybindings: [
        monaco.KeyMod.CtrlCmd | monaco.KeyCode.KEY_S,
    ],
    precondition: window.dirty === true,
    keybindingContext: null,
    contextMenuGroupId: 'editor',
    contextMenuOrder: 1.5,
    run: function(ed) {
        if (window.dirty) {
            window.qzwrapper.save();
            window.contentID = getContentID();
        }
        return null;
    }
});

window.editor = editor;
window.dirty = false;
window.contentID = null;

window.editor.getModel().onDidChangeContent(function() {
    let newID = getContentID();
    if (window.contentID && window.contentID !== newID) {
        window.dirty = true;
        if (window.qzwrapper) {
            window.qzwrapper.dirtyChanged(window.dirty);
        }
    } else if(window.contentID) {
        let wasDirty = window.dirty;
        window.dirty = false;
        if (wasDirty && window.qzwrapper) {
            window.qzwrapper.dirtyChanged(window.dirty);
        }
    }
});
