<!--<?php
   /**
    * This is a template for the Shanti Grid View Info page loaded into the dropdown via ajax.
    * The strings to replace are (without the asterisks which are to prevent these strings from being replaced):
    *
    *       GV*TYPE : e.g. "node", "file", "data" (Filled in automatically by code)
    *
    *       GV*ID : a unique numeric id, together with type this becomes the id, e.g. "node-1234"
    *       GV*TITLE : the title of the item
    *       GV*AUTH : the markup for the author's name/link
    *       GV*SUBTYPE : the asset subtype
    *       GV*WIDTH : the width of the image
    *       GV*HEIGHT: the height of the image
    *       GV*DATE : the date of the image
    *       GV*COLLECTION : the name/link for the collection
    *       GV*PLACES : the markup for the kmaps place tags
    *       GV*SUBJECTS : the markup for the subjects tags
    *       GV*DESC : the description for this item
    *
    * All the placeholders must be replaced, even if empty, or they will show up in the dropdown.
    */
?>-->
<div id="GVTYPE-GVID" class="GVTYPE grid_details clearfix">
    <div class="ppd-details-inner">
        <h2>GVTITLE</h2>
        <div class="specs">
            <div class="author">GVAUTH</div>
            <div class="size-cnt"><span class="sep"></span><div class="size">GVWIDTHxGVHEIGHT</div></div>
            <span class="sep"></span><div class="date">GVDATE</div>
        </div>
        <div class="subtype">GVSUBTYPE</div>
        <div class="collections">
            <span class="icon shanticon-stack"></span>
            GVCOLLECTION
        </div>
        <div class="kmaps">
            <div class="place">
                <span class="icon shanticon-places"></span>
                GVPLACES
            </div>
        </div>
        <div class="kmaps">
             <div class="subject">
                 <span class="icon shanticon-subjects"></span>
                 GVSUBJECTS
             </div>
        </div>
        <div class="description">
            GVDESC
        </div>
        <div class="links">
            <a href="#" class="btn btn-default btn-sm view-btn">Details
                <span class="icon shanticon-angle-double-right"></span>
            </a>
        </div>
    </div> <!-- END details inner -->
</div> <!-- END details --> 