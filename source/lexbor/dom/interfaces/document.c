/*
 * Copyright (C) 2018 Alexander Borisov
 *
 * Author: Alexander Borisov <lex.borisov@gmail.com>
 */

#include "lexbor/dom/interfaces/document.h"
#include "lexbor/dom/interfaces/element.h"
#include "lexbor/dom/interfaces/text.h"
#include "lexbor/dom/interfaces/document_fragment.h"
#include "lexbor/dom/interfaces/comment.h"


lxb_dom_document_t *
lxb_dom_document_interface_create(lxb_dom_document_t *document)
{
    lxb_dom_document_t *element;

    element = lexbor_mraw_calloc(document->mraw,
                                 sizeof(lxb_dom_document_t));
    if (element == NULL) {
        return NULL;
    }

    lxb_dom_node_t *node = lxb_dom_interface_node(element);

    node->owner_document = lxb_dom_interface_document(document);
    node->type = LXB_DOM_NODE_TYPE_ELEMENT;

    element->create_interface = lxb_dom_interface_create;
    element->destroy_interface = lxb_dom_interface_destroy;

    return element;
}

lxb_dom_document_t *
lxb_dom_document_interface_destroy(lxb_dom_document_t *document)
{
    return lexbor_mraw_free(
        lxb_dom_interface_node(document)->owner_document->mraw,
        document);
}

void
lxb_dom_document_attach_doctype(lxb_dom_document_t *document,
                                lxb_dom_document_type_t *doctype)
{
    document->doctype = doctype;
}

void
lxb_dom_document_attach_element(lxb_dom_document_t *document,
                                lxb_dom_element_t *element)
{
    document->element = element;
}

lxb_dom_element_t *
lxb_dom_document_create_element(lxb_dom_document_t *document,
                                const lxb_char_t *local_name, size_t lname_len,
                                void *reserved_for_opt)
{
    /* TODO: If localName does not match the Name production... */

    const lxb_char_t *ns_link;
    size_t ns_len;
    bool lowercase;

    if (document->type == LXB_DOM_DOCUMENT_DTYPE_HTML) {
        ns_link = (const lxb_char_t *) "http://www.w3.org/1999/xhtml";

        /* FIXME: he will get len at the compilation stage?!? */
        ns_len = strlen((const char *) ns_link);

        lowercase = true;
    }
    else {
        ns_link = NULL;
        ns_len = 0;

        lowercase = false;
    }

    return lxb_dom_element_create(document, local_name, lname_len,
                                  ns_link, ns_len, NULL, 0, NULL, 0,
                                  true, lowercase);
}

lxb_dom_element_t *
lxb_dom_document_destroy_element(lxb_dom_element_t *element)
{
    return lxb_dom_element_destroy(element);
}

lxb_dom_document_fragment_t *
lxb_dom_document_create_document_fragment(lxb_dom_document_t *document)
{
    return lxb_dom_document_fragment_interface_create(document);
}

lxb_dom_text_t *
lxb_dom_document_create_text_node(lxb_dom_document_t *document,
                                  const lxb_char_t *data, size_t len)
{
    lxb_dom_text_t *text;

    text = lxb_dom_document_create_interface(document,
                                             LXB_TAG__TEXT, LXB_NS_HTML);
    if (text == NULL) {
        return NULL;
    }

    lexbor_str_init(&text->char_data.data, document->text, len);
    if (text->char_data.data.data == NULL) {
        return lxb_dom_document_destroy_interface(text);
    }

    lexbor_str_append(&text->char_data.data, document->text, data, len);

    return text;
}

lxb_dom_comment_t *
lxb_dom_document_create_comment(lxb_dom_document_t *document,
                                const lxb_char_t *data, size_t len)
{
    lxb_dom_comment_t *comment;

    comment = lxb_dom_document_create_interface(document, LXB_TAG__EM_COMMENT,
                                                LXB_NS_HTML);
    if (comment == NULL) {
        return NULL;
    }

    lexbor_str_init(&comment->char_data.data, document->text, len);
    if (comment->char_data.data.data == NULL) {
        return lxb_dom_document_destroy_interface(comment);
    }

    lexbor_str_append(&comment->char_data.data, document->text, data, len);

    return comment;
}
