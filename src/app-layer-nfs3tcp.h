/* Copyright (C) 2015 Open Information Security Foundation
 *
 * You can copy, redistribute or modify this Program under the terms of
 * the GNU General Public License version 2 as published by the Free
 * Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * version 2 along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA
 * 02110-1301, USA.
 */

/**
 * \file
 *
 * \author FirstName LastName <yourname@domain>
 */

#ifndef __APP_LAYER_NFS3TCP_H__
#define __APP_LAYER_NFS3TCP_H__

#include "detect-engine-state.h"

#include "queue.h"

void RegisterNfs3TcpParsers(void);
void Nfs3TcpParserRegisterTests(void);

typedef struct Nfs3TcpTransaction_ {

    uint64_t tx_id;             /*<< Internal transaction ID. */

    AppLayerDecoderEvents *decoder_events; /*<< Application layer
                                            * events that occurred
                                            * while parsing this
                                            * transaction. */

    uint8_t *request_buffer;
    uint32_t request_buffer_len;

    /* flags indicating which loggers that have logged */
    uint32_t logged;

    uint8_t *response_buffer;
    uint32_t response_buffer_len;

    uint8_t response_done; /*<< Flag to be set when the response is
                            * seen. */

    DetectEngineState *de_state;

    TAILQ_ENTRY(Nfs3TcpTransaction_) next;

} Nfs3TcpTransaction;

typedef struct Nfs3TcpState_ {

    TAILQ_HEAD(, Nfs3TcpTransaction_) tx_list; /**< List of Nfs3Tcp transactions
                                       * associated with this
                                       * state. */

    uint64_t transaction_max; /**< A count of the number of
                               * transactions created.  The
                               * transaction ID for each transaction
                               * is allocted by incrementing this
                               * value. */

    uint16_t events; /**< Number of application layer events created
                      * for this state. */

} Nfs3TcpState;

#endif /* __APP_LAYER_NFS3TCP_H__ */